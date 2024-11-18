#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <cstdint>
#include <sstream>
#include <unordered_set>
using namespace std;


array<uint32_t, 32> registers;
uint32_t progcount = 0; 
vector<pair<uint32_t, uint32_t>> memory_access; 
unordered_set<string> stopCommands = {"ECALL", "EBREAK", "PAUSE", "FENCE", "FENCE.TSO"};

bool Valid(uint8_t r){
    if (r >= 32) {
        cerr << "Invalid register index!" << endl;
        return false;
    }
    if(r==0 ) {
        cerr << "Register Zero Cannot be overwritten" << endl;
        return false;
    }
    return true;
}

uint8_t GetReg(string regname){
    stringstream ss(regname);
    char prefix;
    uint8_t regNumber;

    ss >> prefix >> regNumber;  
    if (prefix != 'r' || ss.fail()) {
        throw invalid_argument("Invalid register format");
    }
    return regNumber;

}

void ADD(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 + value_rs2;

    registers[rd] = result;

    cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " (" 
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}

}

void ADDI(uint8_t rd, uint8_t rs1, int32_t Imm) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 + Imm;

    registers[rd] = result;

     cout << "ADDI: R" << +rd << " = R" << +rs1 << " (" 
              << value_rs1 << " + " << Imm << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}

    }

void Sim(vector<string> lines){
     int commandCount = lines.size();
    string outputString;


    for (int i = 0; i < commandCount; ++i) {
            string command = lines[i]; 

        
           if (stopCommands.count(command)) {
            return;
        }
    istringstream ss(command);
    string opcode, rd, rs1, rs2, imm;
    ss >> opcode;
    
        if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" || opcode == "SLL" || opcode == "SLT"|| opcode == "SLTU" || opcode == "SRL" || opcode == "SRA" || opcode == "XOR") {
        
        ss >> rd >> rs1 >> rs2;
        } 
    else if (opcode == "ADDI" || opcode == "ANDI" || opcode == "ORI" || opcode == "LW"||opcode == "SLTI" || opcode == "SLTIU" || opcode == "XORI" || opcode == "SLLI"||opcode == "SRLI" || opcode == "SRAI" || opcode == "LB" || opcode == "LH "||opcode == "LBU" || opcode == "LHU" || opcode == "JALR") {
        
        ss >> rd >> rs1 >> imm;
       } 
    else if (opcode == "SW"||opcode == "SB"||opcode == "SH") {
       ss >> rs1 >> rs2 >> imm;
        } 
    else if (opcode == "BEQ" || opcode == "BNE"||opcode == "BLT" || opcode == "BGE" || opcode == "BLTU"|| opcode == "BGEU") {
          ss >> rs1 >> rs2 >> imm;
         } 
    else if (opcode == "LUI" || opcode == "auipc") {
        ss >> rd >> imm;
        } 
    else if (opcode == "JAL") {
        ss >> rd >> imm;
         } 
    else {
        cerr << "Unknown instruction format or opcode: " << opcode << "\n";
    }

    if (opcode== "ADD") {
                ADD(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SUB") {
                //SUB(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "AND") {
                //AND(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "OR") {
                //OR(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLL") {
                //SLL(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLT") {
                //SLT(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLTU") {
                //SLT(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "XOR") {
                //XOR(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SRL") {
                //SRL(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SRA") {
                //SRA(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }

    }
}


