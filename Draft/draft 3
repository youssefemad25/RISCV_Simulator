#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <utility>
#include <cstdint>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <cstdlib>
using namespace std;


array<uint32_t, 32> registers;
uint32_t progcount = 0;
vector<pair<string,int>> branch;
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

vector<string> readFileToVector(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file: " << filePath << endl;
        return {};
    }

    vector<string> fileContents;
    string line;

    while (getline(file, line)) {
        if (!line.empty() && !all_of(line.begin(), line.end(), [](unsigned char c) { return isspace(c); })) {
            fileContents.push_back(line);
        }
    }

    file.close();
    return fileContents;
}

void writeVectorToFile(const string& filePath,const vector<string>& output) {


    ofstream file(filePath);
    if (!file) {
        throw std::ios_base::failure("Failed to open file: " + filePath);
    }

    
    for (const auto& line : output) {
        file << line << '\n';
    }
    
    file.close();
}

uint8_t GetReg(string regname){
    stringstream ss(regname);
    char prefix;
    int regNumber;

    ss >> prefix >> regNumber;
    if (prefix != 'r' || ss.fail()) {
        throw invalid_argument("Invalid register format");
    }
    return regNumber;

}
int get_content(int address)
{
    for(int i=0;i<memory_access.size();i++)
    {
        if(memory_access[i].first==address)
            return memory_access[i].second;
    }
    
    cerr << "Error: Memory address " << address << " not found. Returning default value 0." << endl;
    return 0;
}

int get_line(string name)
{
    for(int i=0;i<branch.size();i++)
    {
        if(branch[i].first==name)
            return branch[i].second;
    }
    
    cerr << "Error: Branch " << name << " not found. Returning default value 0." << endl;
    return 0;
}

void store_content(int address, int content)
{
    for(int i=0;i<memory_access.size();i++)
    {
        if(memory_access[i].first==address)
             memory_access[i].second=content;
    }
    
    cerr <<
 "Error: Memory address " << address << " not found." << endl;
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

void SLT(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    if(value_rs1 < value_rs2){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


   /* cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    */
   }

}

void SLTU(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    int value_rs1 = registers[rs1];
    int value_rs2 = registers[rs2];

    if( abs(value_rs1) < abs(value_rs2)){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


   /* cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    */
   }

}

void SLTIU(uint8_t rd, uint8_t rs1, int imm) {
    if(Valid(rd) && Valid(rs1)){
    progcount+=1;
    int value_rs1 = registers[rs1];

    if( abs(value_rs1) < abs(imm)){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


   /* cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    */
   }

}

void SUB(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 - value_rs2;

    registers[rd] = result;

    cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}
}

void AND(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 & value_rs2;

    registers[rd] = result;

    cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}
}

void OR(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 | value_rs2;

    registers[rd] = result;

    cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}
}

void XOR(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 ^ value_rs2;

    registers[rd] = result;

    cout << "ADD: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}
}


void SLL(int rd, int rs1, int rs2)
{
    if(Valid(rd) && Valid(rs1) && Valid(rs2))
    {
    registers[rd]=registers[rs1] << (registers[rs2]&0b11111);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
}
}


void ADDI(uint8_t rd, uint8_t rs1, int32_t Imm) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 + Imm;

    registers[rd] = result;

     cout << "ADDI: R" << rd << " = R" << rs1 << " ("
              << value_rs1 << " + " << Imm << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}
    }


    void ANDI(uint8_t rd, uint8_t rs1, int32_t Imm) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 & Imm;

    registers[rd] = result;

     cout << "ADDI: R" << +rd << " = R" << +rs1 << " ("
              << value_rs1 << " + " << Imm << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}

    }

    void ORI(uint8_t rd, uint8_t rs1, int32_t Imm) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 | Imm;

    registers[rd] = result;

     cout << "ADDI: R" << +rd << " = R" << +rs1 << " ("
              << value_rs1 << " + " << Imm << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}

    }

    void XORI(uint8_t rd, uint8_t rs1, int32_t Imm) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 ^ Imm;

    registers[rd] = result;

     cout << "ADDI: R" << +rd << " = R" << +rs1 << " ("
              << value_rs1 << " + " << Imm << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;}

    }


  void LUI(int rd, int immediate)
{
    if(Valid(rd))
    {
    
    immediate=immediate&0xFFFFF;
    registers[rd]=immediate << 12;
    progcount++;

    cout << "LUI: R" << rd << "," << immediate << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}
void SLLI(int rd, int rs1, int imm)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=registers[rs1] << (imm&0b11111);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
    }

void AUIPC(int rd, int immediate)
{
    if(Valid(rd))
    {
        
    immediate=immediate&0xFFFFF;
    registers[rd]=progcount+(immediate << 12);
    progcount++;
    
    cout << "AUIPC: R" << rd << "," << immediate << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}


void JAL(int rd, int immediate)
{
    if(Valid(rd))
    {

    registers[rd]=1+progcount;
    progcount=(progcount)+(immediate << 1);
    progcount++;
        
    cout << "JAL: R" << rd << "," << immediate << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void JALR(int rd, int rs1, int immediate)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=1+progcount;
    progcount=(registers[rs1])+(immediate << 2);
    cout << "JALR: R" << rd << ", R" << rs1 << ", " << immediate << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}


void LHU(int rd, int rs1, int offset)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address1=registers[rs1];
    address1+=offset*4;
    int address2=address1+1;
    int content1=get_content(address1);
    int content2=get_content(address2);
    registers[rd]=content2 << 24;
    registers[rd]=registers[rd]+(content1 << 16);
    progcount++;
    cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void SW(int rs1, int rs2, int offset)
{
    if(Valid(rs1) && Valid(rs2))
    {
    int address1=registers[rs2];
    address1+=offset*4;
    int address2=address1+1;
    int address3=address2+1;
    int address4=address3+1;
    int content1=(registers[rs1])&0xFF;
    int content2=(registers[rs1] >> 8)&0xFF;
    int content3=(registers[rs1] >> 16)&0xFF;
    int content4=(registers[rs1] >> 24)&0xFF;
    store_content(address1,content1);
    store_content(address2,content2);
    store_content(address3,content3);
    store_content(address4,content4);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void SH(int rs1, int rs2, int offset)
{
    if(Valid(rs1) && Valid(rs2))
    {
    int address1=registers[rs2];
    address1+=offset*4;
    int address2=address1+1;
    int content1=(registers[rs1])&0xFF;
    int content2=(registers[rs1] >> 8)&0xFF;
    store_content(address1,content1);
    store_content(address2,content2);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void SB(int rs1, int rs2, int offset)
{
    if(Valid(rs1) && Valid(rs2))
    {
    int address1=registers[rs2];
    address1+=offset*4;
    int content1=(registers[rs1])&0xFF;
    store_content(address1,content1);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
   }
}



void BEQ(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]==registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
    //cout << "BEQ: R" << rs1 << ", R" << rs2 << ", " << branch << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void BNE(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]!=registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
    //cout << "BNE: R" << rd << ", R" << rs1 << ", R" << rs2 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void BLT(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]<registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
    //cout << "BLT: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
              //<< value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void BGE(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]>=registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
    //cout << "BGE: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
             // << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void BLTU(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]<0)
        registers[rs1]=-registers[rs1];
    
    if(registers[rs2]<0)
        registers[rs2]=-registers[rs2];
    
    if(registers[rs1]<registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
    //cout << "BLTU: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
      //        << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void BGEU(int rs1, int rs2, string branch)
{
    if(Valid(rs1) && Valid(rs2))
    {
    if(registers[rs1]<0)
        registers[rs1]=-registers[rs1];
    
    if(registers[rs2]<0)
        registers[rs2]=-registers[rs2];
    
    if(registers[rs1]>=registers[rs2])
    {
        int branchnum=get_line(branch);
        progcount=branchnum;
    }
    else
    {
        progcount++;
    }
   // cout << "BGEU: R" << +rd << " = R" << +rs1 << " + R" << +rs2 << " ("
     //         << value_rs1 << " + " << value_rs2 << " = " << result << ")" << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void LB(int rd, int rs1, int offset)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address=registers[rs1];
    address+=offset*4;
    int content=get_content(address);
    registers[rd]=content;
    progcount++;
    cout << "LB: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void LH(int rd, int rs1, int offset)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address1=registers[rs1];
    address1+=offset*4;
    int address2=address1+1;
    int content1=get_content(address1);
    int content2=get_content(address2);
    registers[rd]=content2 << 8;
    registers[rd]=registers[rd]+content1;
    progcount++;
    cout << "LH: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void LW(int rd, int rs1, int offset)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address1=registers[rs1];
    address1+=offset*4;
    int address2=address1+1;
    int address3=address2+1;
    int address4=address3+1;
    int content1=get_content(address1);
    int content2=get_content(address2);
    int content3=get_content(address3);
    int content4=get_content(address4);
    registers[rd]=content4 << 24;
    registers[rd]=registers[rd]+(content3 << 16);
    registers[rd]=registers[rd]+(content2 << 8);
    registers[rd]=registers[rd]+content1;
    progcount++;
    cout << "LW: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
        std::bitset<32> binary(registers[rd]); // Change 32 to the number of bits you want
        std::cout << "Binary (bitset): " << binary << std::endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}

void LBU(int rd, int rs1, int offset)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address=registers[rs1];
    address+=offset*4;
    int content=get_content(address);
    registers[rd]=content << 24;
    progcount++;
    cout << "LBU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
}


void SRL(int rd, int rs1, int rs2)
{
    if(Valid(rd) && Valid(rs1) && Valid(rs2))
    {
    registers[rd]=registers[rs1] >> (registers[rs2]&0b11111);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
    
}

void SRA(int rd, int rs1, int rs2)
{
    if(Valid(rd) && Valid(rs1) && Valid(rs2))
    {
    int shift_amount=registers[rs2]&0b11111;
    if(registers[rs1]>>31==0)
    {
        registers[rd]=registers[rs1] >> (registers[rs2]&0b11111);
    }
    else
    {
    registers[rd]=registers[rs1] >> (registers[rs2]&0b11111);
    for(int i=1; i<shift_amount;i++)
    {
        registers[rd] |= (1 << (32-i));
    }
    }
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
    
}

void SRLI(int rd, int rs1, int immediate)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=registers[rs1] >> (immediate&0b11111);
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
    }
    
}

void SRAI(int rd, int rs1, int immediate)
{
    if(Valid(rd) && Valid(rs1))
    {
    int shift_amount=immediate&0b11111;
    if(registers[rs1]>>31==0)
    {
        registers[rd]=registers[rs1] >> (immediate&0b11111);
    }
    else
    {
    registers[rd]=registers[rs1] >> (immediate&0b11111);
    for(int i=1; i<shift_amount;i++)
    {
        registers[rd] |= (1 << (32-i));
    }
    }
    progcount++;
    //cout << "LHU: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
    cout << "Updated Program Count: " << progcount  << endl;
        
    }
    
}


void Sim(vector<string> lines){
     int commandCount = lines.size();
    string outputString;


    for (int i = 0; i < commandCount; ++i) {
            string command = lines[i];

        replace(command.begin(), command.end(), ',', ' ');

           if (stopCommands.count(command)) {
            return;
        }
    istringstream ss(command);
    string opcode, rd, rs1, rs2,name;
    int imm;
    ss >> opcode;
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    
        if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" ||
        opcode == "SLL" || opcode == "SLT"|| opcode == "SLTU" || opcode == "SRL" || opcode == "SRA"
         || opcode == "XOR") {
        
        ss >> rd >> rs1 >> rs2;
        }
    else if (opcode == "ADDI" || opcode == "ANDI" || opcode == "ORI" || opcode == "LW"
    ||opcode == "SLTI" || opcode == "SLTIU" || opcode == "XORI" || opcode == "SLLI"||opcode == "SRLI"
    || opcode == "SRAI" || opcode == "LB" || opcode == "LH"||opcode == "LBU" || opcode == "LHU" || opcode == "JALR") {
        
        ss >> rd >> rs1 >> imm;
       }
    else if (opcode == "SW"||opcode == "SB"||opcode == "SH") {
       ss >> rs1 >> rs2 >> imm;
        }
    else if (opcode == "BEQ" || opcode == "BNE"||opcode == "BLT" || opcode == "BGE" || opcode == "BLTU"|| opcode == "BGEU") {
          ss >> rs1 >> rs2 >> name;
         }
    else if (opcode == "LUI" || opcode == "auipc") {
        ss >> rd >> imm;
        }
    else if (opcode == "JAL") {
        ss >> rd >> imm;
         }
    else {
        branch.push_back(make_pair(opcode, i));
        istringstream ss(command);
    string opcode1, rd, rs1, rs2;
    int imm;
    ss >> opcode1;
    transform(opcode1.begin(), opcode1.end(), opcode1.begin(), ::toupper);
      if (!opcode1.empty() && opcode1[0] == ':') {
        opcode1.erase(0, 1);
    }
    
        if (opcode1 == "ADD" || opcode1 == "SUB" || opcode1 == "AND" || opcode1 == "OR" ||
        opcode1 == "SLL" || opcode1 == "SLT"|| opcode1 == "SLTU" || opcode1 == "SRL" || opcode1 == "SRA"
         || opcode1 == "XOR") {
        
        ss >> rd >> rs1 >> rs2;
        }
    else if (opcode1 == "ADDI" || opcode1 == "ANDI" || opcode1 == "ORI" || opcode1 == "LW"
    ||opcode1 == "SLTI" || opcode1 == "SLTIU" || opcode1 == "XORI" || opcode1 == "SLLI"||opcode1 == "SRLI"
    || opcode1 == "SRAI" || opcode1 == "LB" || opcode1 == "LH"||opcode1 == "LBU" || opcode1 == "LHU" || opcode1 == "JALR") {
        
        ss >> rd >> rs1 >> imm;
       }
    else if (opcode1 == "SW"||opcode1 == "SB"||opcode1 == "SH") {
       ss >> rs1 >> rs2 >> imm;
        }
    else if (opcode1 == "BEQ" || opcode1 == "BNE"||opcode1 == "BLT" || opcode1 == "BGE" || opcode1 == "BLTU"|| opcode1 == "BGEU") {
          ss >> rs1 >> rs2 >> imm;
         }
    else if (opcode1 == "LUI" || opcode1 == "auipc") {
        ss >> rd >> imm;
        }
    else if (opcode1 == "JAL") {
        ss >> rd >> imm;
         }
         else {
        cerr << "Unknown instruction format or opcode: " << opcode << "\n";
    }
    opcode = opcode1;

    }

    if (opcode== "ADD") {
                ADD(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SUB") {
                SUB(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "AND") {
                AND(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "OR") {
                OR(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLL") {
                SLL(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLT") {
                SLT(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SLTU") {
                SLTU(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "XOR") {
                XOR(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SRL") {
                SRL(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "SRA") {
                SRA(GetReg(rd),GetReg(rs1),GetReg(rs2));
            }
    else if (opcode== "ADDI") {
                ADDI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "ANDI") {
                ANDI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "ORI") {
                ORI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "LW") {
                LW(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "SLTIU") {
                SLTIU(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "XORI") {
                XORI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "SLLI") {
                SLLI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "SRLI") {
                SRLI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "SRAI") {
                SRAI(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "LB") {
                LB(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "LH") {
                LH(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "LBU") {
                LBU(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "LHU") {
                LHU(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "JALR") {
                JALR(GetReg(rd),GetReg(rs1),imm);
            }
    else if (opcode== "SW") {
                SW(GetReg(rs1),GetReg(rs2),imm);
            }
    else if (opcode== "SB") {
                SB(GetReg(rs1),GetReg(rs2),imm);
            }
    else if (opcode== "SH") {
                SH(GetReg(rs1),GetReg(rs2),imm);
            }
    else if (opcode== "BEQ") {
                BEQ(GetReg(rs1),GetReg(rs2), name);
            }
    else if (opcode== "BNE") {
                BNE(GetReg(rs1),GetReg(rs2),name);
            }
    else if (opcode== "BLT") {
                BLT(GetReg(rs1),GetReg(rs2),name);
            }
    else if (opcode== "BGE") {
                BGE(GetReg(rs1),GetReg(rs2),name);
            }
    else if (opcode== "BLTU") {
                BLTU(GetReg(rs1),GetReg(rs2),name);
            }
    else if (opcode== "BGEU") {
                BGEU(GetReg(rs1),GetReg(rs2),name);
            }
    else if (opcode== "LUI") {
                LUI(GetReg(rd),imm);
            }
    else if (opcode== "auipc") {
                AUIPC(GetReg(rd),imm);
            }
    else if (opcode== "JAL") {
                JAL(GetReg(rd),imm);
            }

    }
}

int main()
{
    for(int i=0;i<1000;i++)
    {
        memory_access.emplace_back(i, rand()%256);
    }
    cout << memory_access[416].first << "," << memory_access[416].second << endl;
    cout << memory_access[417].first << "," << memory_access[417].second << endl;
    cout << memory_access[418].first << "," << memory_access[418].second << endl;
    cout << memory_access[419].first << "," << memory_access[419].second << endl;
    string filepath;
    filepath="/Users/youssefibrahim/Desktop/1/test.txt";
    vector<string> commands=readFileToVector(filepath);
    Sim(commands);
    
    return 0;
}
