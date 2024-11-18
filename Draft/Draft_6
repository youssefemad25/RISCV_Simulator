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

void print_memory(vector<string>& Output)
{
    cout << "current memory: \n";
    for(int i=0;i<memory_access.size();i++)
    {
        string output = to_string(memory_access[i].first) + " " + to_string(memory_access[i].second) + "\n";

cout << output;
Output.push_back(output);
    }
}

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
        {
            memory_access[i].second=content;
            return;
        }
    }
    
    cerr << "Error: Memory address " << address << " not found." << endl;
}


void ADD(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 + value_rs2;

    registers[rd] = result;

    string output = "ADD: R" + to_string(rd) + " = R" + to_string(rs1) + " + R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " + " + to_string(value_rs2) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);
    
    }

}

void SLT(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    if(value_rs1 < value_rs2){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


   string output = "SLT: R" + to_string(rd) + " set if R" + to_string(rs1) +
                " is less than R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " < " + to_string(value_rs2) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    
    }
   }



void SLTU(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    int value_rs1 = registers[rs1];
    int value_rs2 = registers[rs2];

    if( abs(value_rs1) < abs(value_rs2)){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


    string output = "SLTU: R" + to_string(rd) + " set if unsigned value of R" + to_string(rs1) +
                " is less than R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " < " + to_string(value_rs2) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);
    }
   }



void SLTIU(uint8_t rd, uint8_t rs1, int imm,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1)){
    progcount+=1;
    int value_rs1 = registers[rs1];

    if( abs(value_rs1) < abs(imm)){

    registers[rd] = 1;
    }else{
       registers[rd] = 0;
    }


   string output = "SLTIU: R" + to_string(rd) + " set if unsigned value of R" + to_string(rs1) +
                " is less than " + to_string(imm) +
                " (" + to_string(value_rs1) + " < " + to_string(imm) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
   }


void SUB(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 - value_rs2;

    registers[rd] = result;

    string output = "SUB: R" + to_string(rd) + " = R" + to_string(rs1) + " - R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " - " + to_string(value_rs2) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void AND(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 & value_rs2;

    registers[rd] = result;

    string output = "AND: R" + to_string(rd) + " = R" + to_string(rs1) + " & R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " & " + to_string(value_rs2) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);
}
}

void OR(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 | value_rs2;

    registers[rd] = result;

    string output = "OR: R" + to_string(rd) + " = R" + to_string(rs1) + " | R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " | " + to_string(value_rs2) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
}

void XOR(uint8_t rd, uint8_t rs1, uint8_t rs2,vector<string>& Output){
    if(Valid(rd) && Valid(rs1) && Valid(rs2)){
    progcount+=1;
    uint32_t value_rs1 = registers[rs1];
    uint32_t value_rs2 = registers[rs2];

    uint32_t result = value_rs1 ^ value_rs2;

    registers[rd] = result;

    string output = "XOR: R" + to_string(rd) + " = R" + to_string(rs1) + " ^ R" + to_string(rs2) +
                " (" + to_string(value_rs1) + " ^ " + to_string(value_rs2) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}


void SLL(int rd, int rs1, int rs2,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1) && Valid(rs2))
    {
    registers[rd]=registers[rs1] << (registers[rs2]&0b11111);
    progcount++;

      string output = "SLL: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted left logically by R" + to_string(rs2) +
                " (" + to_string(registers[rs1]) + " << " + to_string(registers[rs2]) +
                " = " + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

}
}


void ADDI(uint8_t rd, uint8_t rs1, int32_t Imm,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) ){
        progcount+=1;
        int32_t value_rs1 = registers[rs1];

    int32_t result = value_rs1 + Imm;

    registers[rd] = result;

    string output = "ADDI: R" + to_string(rd) + " = R" + to_string(rs1) + " + " + to_string(Imm) +
                " (" + to_string(value_rs1) + " + " + to_string(Imm) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
    }


    void ANDI(uint8_t rd, uint8_t rs1, int32_t Imm,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) ){
        int32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 & Imm;

    registers[rd] = result;

     string output = "ANDI: R" + to_string(rd) + " = R" + to_string(rs1) + " & " + to_string(Imm) +
                " (" + to_string(value_rs1) + " & " + to_string(Imm) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }

    }

    void ORI(uint8_t rd, uint8_t rs1, int32_t Imm,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 | Imm;

    registers[rd] = result;

     string output = "ORI: R" + to_string(rd) + " = R" + to_string(rs1) + " | " + to_string(Imm) +
                " (" + to_string(value_rs1) + " | " + to_string(Imm) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }

    }

    void XORI(uint8_t rd, uint8_t rs1, int32_t Imm,vector<string>& Output) {
    if(Valid(rd) && Valid(rs1) ){
        uint32_t value_rs1 = registers[rs1];

    uint32_t result = value_rs1 ^ Imm;

    registers[rd] = result;

    string output = "XORI: R" + to_string(rd) + " = R" + to_string(rs1) + " ^ " + to_string(Imm) +
                " (" + to_string(value_rs1) + " ^ " + to_string(Imm) +
                " = " + to_string(result) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }

    }


  void LUI(int rd, int immediate,vector<string>& Output)
{
    if(Valid(rd))
    {
    
    immediate=immediate&0xFFFFF;
    registers[rd]=immediate << 12;
    progcount++;

    string output = "LUI: R" + to_string(rd) + "," + to_string(immediate) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}
void SLLI(int rd, int rs1, int imm,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=registers[rs1] << (imm&0b11111);
    progcount++;

    string output = "SLLI: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted left logically by " + to_string(imm) +
                " (" + to_string(registers[rs1]) + " << " + to_string(imm) +
                " = " + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
    }

void AUIPC(int rd, int immediate,vector<string>& Output)
{
    if(Valid(rd))
    {
        
    immediate=immediate&0xFFFFF;
    registers[rd]=progcount+(immediate << 12);
    progcount++;
    
    string output = "AUIPC: R" + to_string(rd) + "," + to_string(immediate) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}


void JAL(int rd, int immediate,vector<string>& Output)
{
    if(Valid(rd))
    {

    registers[rd]=1+progcount;
    progcount=(progcount)+(immediate << 1);
    progcount++;
        
    string output = "JAL: R" + to_string(rd) + "," + to_string(immediate) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void JALR(int rd, int rs1, int immediate,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=1+progcount;
    progcount=(registers[rs1])+(immediate << 2);
    string output = "JALR: R" + to_string(rd) + ", R" + to_string(rs1) + ", " + to_string(immediate) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}


void LHU(int rd, int rs1, int offset,vector<string>& Output)
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
    string output = "LHU: R" + to_string(rd) + ", (" + to_string(offset) + ")" + "R" + to_string(rs1) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void SW(int rs1, int rs2, int offset, vector<string>& Output)
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
   
   string output = "SW: Content of word R" + to_string(rs2) + " is stored in the memory starting from address " 
                     + to_string(registers[rs1]) + " with an offset of " + to_string(offset) + "\n" +
                     "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);
    print_memory(Output);
    }
}

void SH(int rs1, int rs2, int offset, vector<string>& Output)
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
    string output = "SH: Content of halfword R" + to_string(rs2) + " is stored in the memory starting from address " 
                + to_string(registers[rs1]) + " with an offset of " + to_string(offset) + "\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);
    print_memory(Output);

    }
}

void SB(int rs1, int rs2, int offset, vector<string>& Output)
{
    if(Valid(rs1) && Valid(rs2))
    {
    int address1=registers[rs2];
    address1+=offset*4;
    int content1=(registers[rs1])&0xFF;
    store_content(address1,content1);
    progcount++;
    string output = "SB: Content of R" + to_string(rs2) + " is stored in the memory starting from address " 
    + to_string(registers[rs1]) + " with an offset of " + to_string(offset) + "\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);
    print_memory(Output);

   }
}



void BEQ(int rs1, int rs2, string branch,vector<string>& Output)
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
    string output = "BEQ: Branch to " + branch + " if R" + to_string(rs1) + " is equal to R" + to_string(rs2) + "\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void BNE(int rs1, int rs2, string branch,vector<string>& Output)
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
    string output = "BNE: Branch to " + branch + " if R" + to_string(rs1) + " is not equal to R" + to_string(rs2) + "\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void BLT(int rs1, int rs2, string branch,vector<string>& Output)
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
    string output = "BLT: Branch to " + branch + " if R" + to_string(rs1) + " is less than R" + to_string(rs2) + "\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void BGE(int rs1, int rs2, string branch,vector<string>& Output)
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
    string output = "BGE: Branch to " + branch + " if R" + to_string(rs1) + " is greater than or equal R" + to_string(rs2) + "\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
}

void BLTU(int rs1, int rs2, string branch,vector<string>& Output)
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
    string output = "BLTU: Branch to " + branch + " if unsigned R" + to_string(rs1) + " is less than unsigned R" + to_string(rs2) + "\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
}

void BGEU(int rs1, int rs2, string branch,vector<string>& Output)
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
   string output = "BGEU: Branch to " + branch + " if unsigned R" + to_string(rs1) + " is greater than or equal unsigned R" + to_string(rs2) + "\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
}

void LB(int rd, int rs1, int offset,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address=registers[rs1];
    address+=offset*4;
    int content=get_content(address);
    registers[rd]=content;
    progcount++;
    string output = "LB: R" + to_string(rd) + ", (" + to_string(offset) + ")" + "R" + to_string(rs1) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
}

void LH(int rd, int rs1, int offset,vector<string>& Output)
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
    string output = "LH: R" + to_string(rd) + ", (" + to_string(offset) + ")" + "R" + to_string(rs1) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";
    cout << output;
    Output.push_back(output);

    }
}

void LW(int rd, int rs1, int offset, vector<string>& Output)
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
  /*  cout << "LW: R" << rd << ", (" << offset << ")" << "R" << rs1 << " ( R" << rd << "=" << registers[rd] << endl;
        std::bitset<32> binary(registers[rd]); // Change 32 to the number of bits you want
        std::cout << "Binary (bitset): " << binary << std::endl;*/
    //cout << "Updated Program Count: " << progcount  << endl;
        string output = "LW: R" + to_string(rd) + ", (" + to_string(offset) + ")" + "R" + to_string(rs1) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
        "Updated Program Count: " + to_string(progcount) + "\n";
        cout << output;
        Output.push_back(output);
    }
}

void LBU(int rd, int rs1, int offset,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1))
    {
    int address=registers[rs1];
    address+=offset*4;
    int content=get_content(address);
    registers[rd]=content << 24;
    progcount++;
    string output = "LBU: R" + to_string(rd) + ", (" + to_string(offset) + ")" + "R" + to_string(rs1) + " ( R" + to_string(rd) + "=" + to_string(registers[rd]) + ")\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
}


void SRL(int rd, int rs1, int rs2,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1) && Valid(rs2))
    {
    registers[rd]=registers[rs1] >> (registers[rs2]&0b11111);
    progcount++;
    string output = "SRL: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted right logically by R" + to_string(rs2) + " (" +
    to_string(registers[rs1]) + " << " + to_string(registers[rs2]) + " = " + to_string(registers[rd]) + ")\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
    
}

void SRA(int rd, int rs1, int rs2,vector<string>& Output)
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
    string output = "SRA: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted right arithmetically by R" + to_string(rs2) + " (" +
    to_string(registers[rs1]) + " << " + to_string(registers[rs2]) + " = " + to_string(registers[rd]) + ")\n" +
    "Updated Program Count: " + to_string(progcount) + "\n";

    cout << output;
    Output.push_back(output);

    }
    
}

void SRLI(int rd, int rs1, int immediate,vector<string>& Output)
{
    if(Valid(rd) && Valid(rs1))
    {
    registers[rd]=registers[rs1] >> (immediate&0b11111);
    progcount++;
    string output = "SRLI: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted right logically by " + to_string(immediate) + " (" +
                to_string(registers[rs1]) + " << " + to_string(immediate) + " = " + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

    }
    
}

void SRAI(int rd, int rs1, int immediate,vector<string>& Output)
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
    string output = "SRAI: R" + to_string(rd) + " stores R" + to_string(rs1) + " shifted right arithmetically by " + to_string(immediate) + " (" +
                to_string(registers[rs1]) + " << " + to_string(immediate) + " = " + to_string(registers[rd]) + ")\n" +
                "Updated Program Count: " + to_string(progcount) + "\n";

cout << output;
Output.push_back(output);

        
    }
    
}


void Sim(vector<string> lines,vector<string>& Output){
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
    int imm,offset;
     char openParen, closeParen;
    ss >> opcode;
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    
        if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" ||
        opcode == "SLL" || opcode == "SLT"|| opcode == "SLTU" || opcode == "SRL" || opcode == "SRA"
         || opcode == "XOR") {
        
        ss >> rd >> rs1 >> rs2;
        }
    else if (opcode == "ADDI" || opcode == "ANDI" || opcode == "ORI" 
    ||opcode == "SLTI" || opcode == "SLTIU" || opcode == "XORI" || opcode == "SLLI"||opcode == "SRLI"
    || opcode == "SRAI" || opcode == "JALR") {
        
        ss >> rd >> rs1 >> imm;
       }
    else if (opcode == "SW"||opcode == "SB"||opcode == "SH"||opcode == "LW"||opcode == "LH"||opcode == "LB" || opcode == "LBU" || opcode == "LHU" ) {
       ss >> rs1 >> offset >> openParen >> rs2 >> closeParen;
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
    string opcode1;
    ss >> opcode1;
    transform(opcode1.begin(), opcode1.end(), opcode1.begin(), ::toupper);
      if (!opcode1.empty() && opcode1[0] == ':') {
        opcode1.erase(0, 1);
    }
    if (command.empty()) continue;
    
         if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" ||
        opcode == "SLL" || opcode == "SLT"|| opcode == "SLTU" || opcode == "SRL" || opcode == "SRA"
         || opcode == "XOR") {
        
        ss >> rd >> rs1 >> rs2;
        }
    else if (opcode == "ADDI" || opcode == "ANDI" || opcode == "ORI" 
    ||opcode == "SLTI" || opcode == "SLTIU" || opcode == "XORI" || opcode == "SLLI"||opcode == "SRLI"
    || opcode == "SRAI" || opcode == "JALR") {
        
        ss >> rd >> rs1 >> imm;
       }
    else if (opcode == "SW"||opcode == "SB"||opcode == "SH"||opcode == "LW"||opcode == "LH"||opcode == "LB" || opcode == "LBU" || opcode == "LHU" ) {
       ss >> rd >> offset >> openParen >> rs1 >> closeParen;
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
        cerr << "Unknown instruction format or opcode: " << opcode << "\n";
    }
    opcode = opcode1;

    }

    if (opcode== "ADD") {
                ADD(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SUB") {
                SUB(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "AND") {
                AND(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "OR") {
                OR(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SLL") {
                SLL(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SLT") {
                SLT(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SLTU") {
                SLTU(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "XOR") {
                XOR(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SRL") {
                SRL(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "SRA") {
                SRA(GetReg(rd),GetReg(rs1),GetReg(rs2),Output);
            }
    else if (opcode== "ADDI") {
                ADDI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "ANDI") {
                ANDI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "ORI") {
                ORI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "LW") {
                LW(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "SLTIU") {
                SLTIU(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "XORI") {
                XORI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "SLLI") {
                SLLI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "SRLI") {
                SRLI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "SRAI") {
                SRAI(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "LB") {
                LB(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "LH") {
                LH(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "LBU") {
                LBU(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "LHU") {
                LHU(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "JALR") {
                JALR(GetReg(rd),GetReg(rs1),imm,Output);
            }
    else if (opcode== "SW") {
                SW(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "SB") {
                SB(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "SH") {
                SH(GetReg(rd),GetReg(rs1),offset,Output);
            }
    else if (opcode== "BEQ") {
                BEQ(GetReg(rs1),GetReg(rs2), name,Output);
            }
    else if (opcode== "BNE") {
                BNE(GetReg(rs1),GetReg(rs2),name,Output);
            }
    else if (opcode== "BLT") {
                BLT(GetReg(rs1),GetReg(rs2),name,Output);
            }
    else if (opcode== "BGE") {
                BGE(GetReg(rs1),GetReg(rs2),name,Output);
            }
    else if (opcode== "BLTU") {
                BLTU(GetReg(rs1),GetReg(rs2),name,Output);
            }
    else if (opcode== "BGEU") {
                BGEU(GetReg(rs1),GetReg(rs2),name,Output);
            }
    else if (opcode== "LUI") {
                LUI(GetReg(rd),imm,Output);
            }
    else if (opcode== "auipc") {
                AUIPC(GetReg(rd),imm,Output);
            }
    else if (opcode== "JAL") {
                JAL(GetReg(rd),imm,Output);
            }

    }
}

int main()
{
    vector<string> result;
    for(int i=0;i<10;i++)
    {
        memory_access.emplace_back(i, rand()%256);
    }
    cout << memory_access[3].first << "," << memory_access[3].second << endl;
    cout << memory_access[4].first << "," << memory_access[4].second << endl;
    cout << memory_access[5].first << "," << memory_access[5].second << endl;
    cout << memory_access[6].first << "," << memory_access[6].second << endl;
    string inputfilepath="/Users/youssefibrahim/Desktop/1/test.txt";
    vector<string> commands=readFileToVector(inputfilepath);
    Sim(commands,result);
    string outputfilepath="/Users/youssefibrahim/Desktop/1/test_out.txt";
    writeVectorToFile(outputfilepath,result);
    
    return 0;
}
