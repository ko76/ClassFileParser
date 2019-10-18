#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <array>
#include <map>
#include <string.h>
#include "classStream.hpp"
using namespace std;

unsigned int toInt(char* h){
	std::stringstream ss;
	unsigned int x;
	ss << std::hex << h;
	ss >> x;
	return x;
}

bool checkLittleEndian(){
	int num = 1;

	if (*(char *)&num == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


unsigned short toShort(char* h){
	std::stringstream ss;
	unsigned short x;
	ss << std::hex << h;
	ss >> x;
	return x;
}

unsigned char toChar(char* h){
	char c = (char) (int) strtol(h,NULL,16);
	return c;
}

class ConstantPoolEntry {
	private:
		vector<int> tagInfoNum;
		string tagInfoStr;
		const char* constantType;
		bool isUtf = false;
		int tagVal;
		int entryNum;
		
	public:
		ConstantPoolEntry (){
			entryNum = -1;
		}

		ConstantPoolEntry(const char* type, int val){
			constantType = type;
			tagVal = val;
			entryNum = -1;
		}

		void setEntryNum(int e){
			entryNum = e;
		}

		int getEntryNum(){
			return entryNum;
		}

		void setTagVal(int val){
			tagVal = val;
		}

		void setConstantType(const char* type){
			constantType = type;
		}

		const char* getConstantType(){
			return constantType;
		}

		int getTagVal(){
			return tagVal;
		}

		void setInfoNum(int i){
			tagInfoNum.push_back(i);
		}

		void setInfoStr(string s){
			isUtf = true;
			tagInfoStr = s;
		}

		bool isUTF(){
			return isUtf;
		}

		int getValueAt(int i){
			return tagInfoNum.at(i);
		}

		vector<int> getValuesNum(){
			return tagInfoNum;
		}
		const char* getValuesStr(){
			return tagInfoStr.c_str();
		}

		string getValuesAsString(){
			return tagInfoStr;
		}



		void print(){
			if (entryNum < 10){
				cout << " ";
			}
			cout << "#"<< entryNum << " = "<< constantType;
			for (int i = 0; i < 20 - strlen(constantType); i++){
				cout << " ";
			}
			
			string s("");
			if (!isUtf){
				for (int i = 0; i < tagInfoNum.size();i++){
					s+= "#" + to_string(tagInfoNum.at(i));
					if (i < tagInfoNum.size()-1){
						s+=".";
					}
				}
			} else {
				s = tagInfoStr;
			}
			cout << "\t" << s.c_str();
			cout << "\n";
		}

		~ConstantPoolEntry(){

		}

	

};

vector<ConstantPoolEntry> constantPool;

string getConstantPoolName(short i){
	int k = (int) i;
	while(!constantPool.at(k).isUTF()){
		k = constantPool.at(k).getValueAt(0);
	}
	return constantPool.at(k).getValuesAsString();	
}


class OtherAttribute{
	private:
		short att_name_index;
		int att_length;
		int entryNum;
		string utfname;
		vector<short> info;

	public:
		OtherAttribute(int e){
			att_name_index = 0;
			att_length = 0;
			entryNum = e;
		}
		int getAttributeLength(){
			return att_length;
		}
		short getAttributeNameIndex(){
			return att_name_index;
		}
		void setAttributeLength(int l){
			att_length = l;
		}
		int getEntryNum(){
			return entryNum;
		}
		void addInfo(short s){
			info.push_back(s);
		}
		void setAttributeNameIndex(short i){
			att_name_index = i;
			utfname = getConstantPoolName(att_name_index);
		}
		vector<short> getInfo(){
			return info;
		}
		string getName(){
			return utfname;
		}
		short getInfoAt(int i){
			return info.at(i);
		}
		void print(){
			cout << "----------------Attribute " << entryNum << "-----------------------\n";
			cout << "Attribute Name: #"<< att_name_index << " " << utfname.c_str() <<  "\t Attribute Length: "<< att_length << "\n";
			for (int i = 0; i < att_length; i++){
				cout << info.at(i);
				if (i < att_length - 1){
					cout <<",";
				}
			}
			cout << "\n";
		}
		~OtherAttribute(){
			
		}
};


class CodeAttribute{
	private:
		short att_name_index;
		int att_length;
		int entryNum;
		short max_stack;
		short max_locals;
		int code_length;
		vector<short> code;
		short exception_length;
		vector<int*> exception_table;
		short att_count;
		vector<OtherAttribute> otherAttributes;
		string utfname;

	public:
		CodeAttribute(int e){
			att_name_index = 0;
			att_length = 0;
			entryNum = e;
		}
		int getAttributeLength(){
			return att_length;
		}
		short getAttributeNameIndex(){
			return att_name_index;
		}
		void setAttributeLength(int l){
			att_length = l;
		}
		int getEntryNum(){
			return entryNum;
		}
		void setAttributeNameIndex(short i){
			att_name_index = i;
			utfname = getConstantPoolName(att_name_index);
		}
		void setVals(short c, short d, int e){
			
			max_stack = c;
			max_locals = d;
			code_length = e;
		}
		void setCode(vector<short> c){
			code = c;
		}
		void setExceptionLength(short l){
			exception_length = l;
		}
		void addException(int* s){
			exception_table.push_back(s);
		}
		void setAttributeCount(short a){
			att_count = a;
		}
		void addCode(short c){
			code.push_back(c);
		}
		void addAttribute(OtherAttribute a){
			otherAttributes.push_back(a);
		}
		int getCodeLength(){
			return code_length;
		}
		vector<short> getCode(){
			return code;
		}
		short getExceptionLength(){
			return exception_length;
		}
		short getAttributeCount(){
			return att_count;
		}
		vector<OtherAttribute> getAttributes(){
			return otherAttributes;
		}
		string getName(){
			return utfname;
		}
		void print(){
			cout << "----------------Attribute " << entryNum << "-----------------------\n";
			cout << "Attribute Name: #"<< att_name_index << " " << utfname.c_str() <<  "\t Attribute Length: "<< att_length << "\n";
			cout << "Stacks: " << max_stack << "\t Locals: " << max_locals << "\n";
			cout << "Code Length: "<< code_length << "\n";
			for (int i = 0; i < code_length; i++){
				cout << "  " << i << ": "<< code.at(i);
				cout << "\n";
			}
			cout << "Other Attributes Count: " << att_count;
			cout << "\n";
		}
		~CodeAttribute(){

		}
};






class FieldEntry{
	private:
		string accFlagVal;
		vector<string> accessFlags;
		short nameIndex;
		short desIndex;
		short attCount;
		vector<OtherAttribute> otherAttributes;
		int entryNum;

	public:
		FieldEntry(int e){
			nameIndex = 0;
			desIndex = 0;
			attCount= 0;
			entryNum = e;
		}
		string getAccessFlagBits(){
			return accFlagVal;
		}
		void setAccessFlags(string a, vector<string> f){
			accFlagVal = a;
			accessFlags = f;
		}
		vector<string> getAccessFlags(){
			return accessFlags;
		}
		short getNameIndex(){
			return nameIndex;
		}
		short getDescriptorIndex(){
			return desIndex;
		}
		short getAttributeCount(){
			return attCount;
		}
		void setNameIndex(short i){
			nameIndex = i;
		}
		void setDescriptorIndex(short i){
			desIndex = i;
		}
		void setAttributeCount(short i ){
			attCount = i;
		}
		vector<OtherAttribute> getAttributes(){
			return otherAttributes;
		}
		OtherAttribute getOtherAttributeAt(int i){
			return otherAttributes.at(i);
		}
		void addOtherAttribute(OtherAttribute a){
			otherAttributes.push_back(a);
		}
		void print(){
			cout << "-------------------Field " << entryNum <<"------------------\n";
			cout << "flags: (0x" << accFlagVal.c_str() << ") ";
			for (int i = 0; i < accessFlags.size(); i++){
				cout << accessFlags.at(i);
				if (i < accessFlags.size()-1){
					cout<<", ";
				}
			}
			cout << "\n";
			cout << "Name Index: "<< constantPool.at(nameIndex).getValuesStr() << "\t Descriptor Index: "<< constantPool.at(desIndex).getValuesStr() << "\t Attribute Count: "<< attCount<< "\n";
			for (int i = 0; i < attCount; i++){
				otherAttributes.at(i).print();
				cout <<"\n";
			}
		}
		~FieldEntry(){

		}
};

class MethodEntry{
	private:
		string accFlagVal;
		vector<string> accessFlags;
		short nameIndex;
		short desIndex;
		short attCount;
		vector<CodeAttribute> codeAttributes;
		vector<OtherAttribute> otherAttributes;
		int entryNum;

	public:
		MethodEntry(int e){
			nameIndex = 0;
			desIndex = 0;
			attCount= 0;
			entryNum = e;
		}
		string getAccessFlagBits(){
			return accFlagVal;
		}
		vector<string> getAccessFlags(){
			return accessFlags;
		}
		void setAccessFlags(string a, vector<string> f){
			accFlagVal = a;
			accessFlags = f;
		}
		short getNameIndex(){
			return nameIndex;
		}
		short getDescriptorIndex(){
			return desIndex;
		}
		short getAttributeCount(){
			return attCount;
		}
		void setNameIndex(short i){
			nameIndex = i;
		}
		void setDescriptorIndex(short i){
			desIndex = i;
		}
		void setAttributeCount(short i ){
			attCount = i;
		}
		void addCodeAttribute(CodeAttribute c){
			codeAttributes.push_back(c);
		}
		vector<CodeAttribute> getCodeAttributes(){
			return codeAttributes;
		}
		CodeAttribute getCodeAttributeAt(int i){
			return codeAttributes.at(i);
		}
		void addOtherAttribute(OtherAttribute a){
			otherAttributes.push_back(a);
		}
		vector<OtherAttribute> getOtherAttributes(){
			return otherAttributes;
		}
		OtherAttribute getOtherAttributeAt(int i){
			return otherAttributes.at(i);
		}
		void print(){
			cout << "---------------Method "<< entryNum << "---------------\n";
			cout << "flags: (0x" << accFlagVal.c_str() << ") ";
			for (int i = 0; i < accessFlags.size(); i++){
				cout << accessFlags.at(i);
				if (i < accessFlags.size()-1){
					cout<<", ";
				}
			}
			cout << "\n";
			cout << "Name Index: "<< constantPool.at(nameIndex).getValuesStr()<< "\t Descriptor Index: "<< constantPool.at(desIndex).getValuesStr() << "\t Attribute Count: "<< attCount<< "\n";
			for (int i = 0; i < otherAttributes.size(); i++){
				otherAttributes.at(i).print();
				cout <<"\n";
			}
			for (int i = 0; i < codeAttributes.size(); i++){
				codeAttributes.at(i).print();
				cout << "\n";
			}
		}
		~MethodEntry(){

		}
};




classStream stream;

ConstantPoolEntry parseEntry(int t){
	ConstantPoolEntry c = ConstantPoolEntry();
	int utflen= 0;
	string bytearr("");
	char k1[3];
	char k2[5];
	char k3[9];
	switch(t){
		case 7:
			c.setTagVal(7);
			c.setConstantType( "Class");
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 9:
			//"class_index"
			//"name_and_type_index");
			c.setTagVal(9);
			c.setConstantType( "Fieldref" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 10:
			//"class_index");
			//"name_and_type_index");

			c.setTagVal(10);
			c.setConstantType( "Methodref");
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 11:
			//"class_index"] = make_tuple(2,NULL,NULL);
			//"name_and_type_index");
			c.setTagVal(11);
			c.setConstantType( "InterfaceMethodref" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 8:
			//"string_index");
			c.setTagVal(8);
			c.setConstantType( "String" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 3:
			//"bytes");
			c.setTagVal(3);
			c.setConstantType( "Integer" );
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			break;
		case 4:
			//"bytes");
			c.setTagVal(4);
			c.setConstantType( "Float" );
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			break;
		case 5:
			//"high_bytes");
			//"low_bytes");
			c.setTagVal(5);
			c.setConstantType( "Long" );
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			break;
		case 6:
			//"high_bytes");
			//"low_bytes");
			c.setTagVal(6);
			c.setConstantType( "Double" );
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			stream.nextInHex(k3,9);
			c.setInfoNum(toInt(k3));
			break;
		case 12:
			//"name_index");
			//"descriptor_index");
			c.setTagVal(12);
			c.setConstantType( "NameAndType" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 1:
			//"length"] = make_tuple(2,NULL,NULL);
			//"byte_array"] = make_tuple(-1,NULL,NULL); // means depends on length
			c.setTagVal(1);
			c.setConstantType( "Utf8" );
			stream.nextInHex(k2,5);
			utflen = (int)toShort(k2);
			c.setInfoNum(utflen);
			for (int i = 0; i < utflen; i++){
				stream.nextInHex(k1,3);
				bytearr += toChar(k1);
				//cout << "\n" << k1 << "\n";
			}
			c.setInfoStr(bytearr);
			break;
		case 15:
			//"reference_kind"] = make_tuple(1,NULL,NULL);
			//"reference_index"] = make_tuple(2,NULL,NULL);
			c.setTagVal(15);
			c.setConstantType( "MethodHandle" );
			stream.nextInHex(k1,3);
			c.setInfoNum((int)toInt(k1));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));	
			break;
		case 16:

			//"descriptor_index"] = make_tuple(2,NULL,NULL);
			c.setTagVal(16);
			c.setConstantType( "MethodType" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 18:
			//"bootstrap_method_attr_index"] = make_tuple(2,NULL,NULL);
			//"name_and_type_index"] = make_tuple(2,NULL,NULL);
			c.setTagVal(18);
			c.setConstantType( "InvokeDynamic" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 19:
			//"name_index"] = make_tuple(2,NULL,NULL);
			c.setTagVal(19);
			c.setConstantType( "Module" );
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		case 20:
			//"name_index"] = make_tuple(2,NULL,NULL);
			c.setTagVal(20);
			c.setConstantType( "Package");
			stream.nextInHex(k2,5);
			c.setInfoNum((int)toShort(k2));
			break;
		default:
			return c;
	}
	return c;
}

bool isLittleEndian = checkLittleEndian();
bool isClass = true;
int classFileSize = 0;
char magic[9];
short minorVersion = 0;
short majorVersion = 0;
char acc_flgs[5];
vector<string> access_Flags;
short cp_Count = 0;
short this_class_index = 0;
short super_class_index = 0;
short interfaces_count = 0;
vector<short> interfacesIndex;
short fields_count = 0;
vector<FieldEntry> fields;
short methods_count = 0;
vector<MethodEntry> methods;
short attributes_count = 0;
vector<OtherAttribute> attributes;



void printVar(char* var, string name){
	cout << name.c_str() << ": "<<var;
	cout << "\n";
}


void printVar(short var, string name){
	cout << name.c_str() << ": " << var;
	cout << "\n";
}

void printAll(){
	printVar(isLittleEndian, "is little endian");
	printVar(classFileSize, "size");
	printVar(magic,"magic");
	printVar(minorVersion, "minor Version");
	printVar(majorVersion, "major Version");
	printVar(cp_Count, "constant pool count");
	
	cout << "flags: (0x" << acc_flgs << ") ";
	for (int i = 0; i < access_Flags.size(); i++){
		cout << access_Flags.at(i);
		if (i < access_Flags.size()-1){
			cout << ", ";
		}
	}
	cout <<"\n";
	int k = (int) this_class_index;
	while(!constantPool.at(k).isUTF()){
		k = constantPool.at(k).getValueAt(0);
	}
	cout << "this_class_index: #" << this_class_index << "\t" << constantPool.at(k).getValuesStr() << "\n";
	k = (int) super_class_index;
	while(!constantPool.at(k).isUTF()){
		k = constantPool.at(k).getValueAt(0);
	}
	cout << "super_class_index: #" << super_class_index << "\t" << constantPool.at(k).getValuesStr() << "\n"; 



	printVar(interfaces_count, "interfaces count");
	printVar(fields_count, "fields count");
	printVar(methods_count, "methods count");


	for (int i = 1; i < cp_Count; i++){
		constantPool.at(i).print();
	}
	for (int i = 0; i < fields_count; i++){
		fields.at(i).print();
	}
	for(int i = 0; i < methods_count; i++){
		methods.at(i).print(); 
	}
	for(int i = 0; i < attributes_count; i++){
		attributes.at(i).print(); 
	}
}

void parseClassFlags(){
	if (acc_flgs[0] == '8'){
		access_Flags.push_back(string("ACC_MODULE"));
		return;
	}
	if (acc_flgs[3] == '1'){
		access_Flags.push_back(string("ACC_PUBLIC"));
	}
	if (acc_flgs[1] == '2' || acc_flgs[1] == '6'){
		access_Flags.push_back(string("ACC_INTERFACE"));
		isClass = false;
		access_Flags.push_back(string("ACC_ABSTRACT"));
		if (acc_flgs[0] == '1'){
			access_Flags.push_back(string("ACC_SYNTHETIC"));
		}
		if (acc_flgs[0] == '2'){
			access_Flags.push_back(string("ACC_ANNOTATION"));
		}
	} else {
		if(acc_flgs[2] == '1'){
			access_Flags.push_back(string("ACC_FINAL"));

		} else if (acc_flgs[2] == '2'){
			access_Flags.push_back(string("ACC_SUPER"));
		} else if (acc_flgs[2] == '3'){
			access_Flags.push_back(string("ACC_FINAL"));
			access_Flags.push_back(string("ACC_SUPER"));
		}

		
		if (acc_flgs[1] == '4' && acc_flgs[2] != '1' && acc_flgs[2] != '3'){
			access_Flags.push_back(string("ACC_ABSTRACT"));
		}
		if (acc_flgs[0] == '1'){
			access_Flags.push_back(string("ACC_SYNTHETIC"));
		}
		if (acc_flgs[0] == '4'){
			access_Flags.push_back(string("ACC_ENUM"));
		}
	}
}

vector<string> parseFieldFlags(char* f){
	vector<string> v;
	if (isClass){
		if (f[3] == '1'){
			v.push_back(string("ACC_PUBLIC"));
		} else if (f[3] == '2'){
			v.push_back(string("ACC_PRIVATE"));
		} else if (f[3] == '4'){
			v.push_back(string("ACC_PROTECTED"));
		} else if (f[3] == '8'){
			v.push_back(string("ACC_STATIC"));
		} else if (f[3] == '9'){
			v.push_back(string("ACC_PUBLIC"));
			v.push_back(string("ACC_STATIC"));	
		} else if (f[3] == 'A' || f[3] == 'a'){
			v.push_back(string("ACC_PRIVATE"));
			v.push_back(string("ACC_STATIC"));
		} else if (f[3] == 'C' || f[3] == 'c'){
			v.push_back(string("ACC_PROTECTED"));
			v.push_back(string("ACC_STATIC"));
		}
		if (f[2] == '1'){
			v.push_back(string("ACC_FINAL"));
		} else if (f[2] == '4'){
			v.push_back(string("ACC_VOLATILE"));
		} else if (f[2] == '8'){
			v.push_back(string("ACC_TRANSIENT"));
		} else if (f[2] == '9'){
			v.push_back(string("ACC_FINAL"));
			v.push_back(string("ACC_TRANSIENT"));
		} else if (f[2] == 'C' || f[2] == 'c'){
			v.push_back(string("ACC_VOLATILE"));
			v.push_back(string("ACC_TRANSIENT"));
		}
		if (f[0] == '1'){
			v.push_back(string("ACC_SYNTHETIC"));
		} else if (f[0] == '4'){
			v.push_back(string("ACC_ENUM"));
		} else if (f[0] == '5'){
			v.push_back(string("ACC_SYNTHETIC"));
			v.push_back(string("ACC_ENUM"));
		}
	} else {
		v.push_back(string("ACC_PUBLIC"));
		v.push_back(string("ACC_STATIC"));
		v.push_back(string("ACC_FINAL"));
		if (f[0] == '1'){
			v.push_back(string("ACC_SYNTHETIC"));
		}
	}
	return v;
}

vector<string> parseMethodFlags(char* f){
	vector<string> v;
	if (f[1] == '4'){
		if (f[3] == '1'){
			v.push_back(string("ACC_PUBLIC"));
		}
		if (isClass){
			if (f[3] == '4'){
				v.push_back(string("ACC_PROTECTED"));
			}
		}
		if (f[2] == '4'){
			v.push_back(string("ACC_BRIDGE"));
		} else if (f[2] == '8'){
			v.push_back(string("ACC_VARARGS"));
		} else if (f[2] == 'C' || f[2] == 'c'){
			v.push_back(string("ACC_BRIDGE"));
			v.push_back(string("ACC_VARARGS"));
		}
		v.push_back(string("ACC_ABSTRACT"));
		if (f[0] == '1'){
			v.push_back(string("ACC_SYNTHETIC"));
		}
	} else {
		if (isClass){
			if (f[3] == '1'){
				v.push_back(string("ACC_PUBLIC"));
			} else if (f[3] == '2'){
				v.push_back(string("ACC_PRIVATE"));
			} else if (f[3] == 4){
				v.push_back(string("ACC_PROTECTED"));
			} else if (f[3] == '9'){
				v.push_back(string("ACC_PUBLIC"));
				v.push_back(string("ACC_STATIC"));
			} else if (f[3] == 'A' || f[3] == 'a'){
				v.push_back(string("ACC_PRIVATE"));
				v.push_back(string("ACC_STATIC"));
			} else if (f[3] == 'C' || f[3] == 'c'){
				v.push_back(string("ACC_PROTECTED"));
				v.push_back(string("ACC_STATIC"));
			}


			if (f[2] == '1'){
				v.push_back(string("ACC_FINAL"));
			} else if (f[2] == '2'){
				v.push_back(string("ACC_SYNCHRONIZED"));
			} else if (f[2] == '3'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_SYNCHRONIZED"));
			} else if (f[2] == '4'){
				v.push_back(string("ACC_BRIDGE"));
			} else if (f[2] == '5'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_BRIDGE"));
			} else if (f[2] == '6'){
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_BRIDGE"));
			} else if (f[2] == '7'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_BRIDGE"));
			} else if (f[2] == '8'){
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == '9'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'A' || f[2] == 'a'){
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'B' || f[2] == 'b'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'C' || f[2] == 'c'){
				v.push_back(string("ACC_BRIDGE"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'D' || f[2] == 'd'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_BRIDGE"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'E' || f[2] == 'e'){
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_BRIDGE"));
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'F' || f[2] == 'f'){
				v.push_back(string("ACC_FINAL"));
				v.push_back(string("ACC_SYNCHRONIZED"));
				v.push_back(string("ACC_BRIDGE"));
				v.push_back(string("ACC_VARARGS"));
			}


			if (f[1] == '1'){
				v.push_back(string("ACC_NATIVE"));
			} else if (f[1] == '8'){
				v.push_back(string("ACC_STRICT"));
			} else if (f[1] == '9'){
				v.push_back(string("ACC_NATIVE"));
				v.push_back(string("ACC_STRICT"));
			}


			if (f[0] == '1'){
				v.push_back(string("ACC_SYNTHETIC"));
			}
		} else {
			if (f[3] == '1'){
				v.push_back(string("ACC_PUBLIC"));
			} else if (f[3] == '2'){
				v.push_back(string("ACC_PRIVATE"));
			}else if (f[3] == '9'){
				v.push_back(string("ACC_PUBLIC"));
				v.push_back(string("ACC_STATIC"));
			} else if (f[3] == 'A' || f[3] == 'a'){
				v.push_back(string("ACC_PRIVATE"));
				v.push_back(string("ACC_STATIC"));
			}


			if (f[2] == '4'){
				v.push_back(string("ACC_BRIDGE"));
			} else if (f[2] == '8'){
				v.push_back(string("ACC_VARARGS"));
			} else if (f[2] == 'C' || f[2] == 'c'){
				v.push_back(string("ACC_BRIDGE"));
				v.push_back(string("ACC_VARARGS"));
			}


			if (f[1] == '8'){
				v.push_back(string("ACC_STRICT"));
			}
			if (f[0] == '1'){
				v.push_back(string("ACC_SYNTHETIC"));
			}
		}
	}
	return v;
}

OtherAttribute createOtherAttribute(int e, short name){
	OtherAttribute a(e);
	a.setAttributeLength(stream.nextInt());
	a.setAttributeNameIndex(name);
	char k[3];
	for (int i = 0; i < a.getAttributeLength(); i++){
		stream.nextInHex(k,3);
		a.addInfo(toShort(k));
	}
	return a;
}

CodeAttribute createCodeAttribute(int e, short name){
	CodeAttribute c(e);
	c.setAttributeNameIndex(name);
	c.setAttributeLength(stream.nextInt());
	short x = stream.nextShort();
	short y = stream.nextShort();
	int z = stream.nextInt();
	c.setVals(x,y,z);
	char k[3];
	for (int i = 0; i < c.getCodeLength(); i++){
		stream.nextInHex(k,3);
		c.addCode(toShort(k));
	}
	c.setExceptionLength(stream.nextShort());
	for (int i = 0; i < c.getExceptionLength();i++){
		int s[4];
		s[0] = stream.nextShort();
		s[1] = stream.nextShort();
		s[2] = stream.nextShort();
		s[3] = stream.nextShort();
		c.addException(s);
	}
	c.setAttributeCount(stream.nextShort());
	for(int i = 0; i < c.getAttributeCount(); i++){
		c.addAttribute(createOtherAttribute(i,stream.nextShort()));
	}
	return c;
}




void parse(vector<char> v){
	stream.setStream(v);
	//stream.print();
	stream.nextInHex(magic,9);
	minorVersion = stream.nextShort();
	majorVersion = stream.nextShort();
	cp_Count = stream.nextShort();	
	char tag[3];
	constantPool.push_back(ConstantPoolEntry());
	for(int i = 1; i < cp_Count; i++){
		stream.nextInHex(tag,3);
		ConstantPoolEntry c = parseEntry(toInt(tag));
		c.setEntryNum(i);
		constantPool.push_back(c);
	}
	stream.nextInHex(acc_flgs,5);
	parseClassFlags();
	if (access_Flags.at(0).compare("ACC_MODULE") == 0){

	} else {
		this_class_index = stream.nextShort();
		super_class_index = stream.nextShort();
		interfaces_count = stream.nextShort();
		for (int i = 0; i < interfaces_count; i++){
			interfacesIndex.push_back(stream.nextShort());
		}
		fields_count = stream.nextShort();
		char fieldAcc[5];
		for (int i = 0; i < fields_count; i++){
			FieldEntry f(i);
			stream.nextInHex(fieldAcc,5);
			f.setAccessFlags(string(fieldAcc),parseFieldFlags(fieldAcc));
			f.setNameIndex(stream.nextShort());
			f.setDescriptorIndex(stream.nextShort());
			f.setAttributeCount(stream.nextShort());
			for (int j = 0; j < f.getAttributeCount(); j++){
				short k = stream.nextShort();
				f.addOtherAttribute(createOtherAttribute(j,k));
				
			}
			fields.push_back(f);
		}
		char methodAcc[5];
		methods_count = stream.nextShort();
		for (int i = 0; i < methods_count; i++){
			MethodEntry m(i);
			stream.nextInHex(methodAcc,5);
			m.setAccessFlags(string(methodAcc),parseMethodFlags(methodAcc));
			m.setNameIndex(stream.nextShort());
			m.setDescriptorIndex(stream.nextShort());
			m.setAttributeCount(stream.nextShort());
			for (int j = 0; j < m.getAttributeCount(); j++){
				short k = stream.nextShort();
				if (getConstantPoolName(k).compare("Code") == 0){
					m.addCodeAttribute(createCodeAttribute(j,k));
				} else {
					m.addOtherAttribute(createOtherAttribute(j,k));
				}
			}
			methods.push_back(m);
		}
	}
	attributes_count = stream.nextShort();
	for (int i = 0; i < attributes_count; i++){
		attributes.push_back(createOtherAttribute(i,stream.nextShort()));
	}
	printAll();
}



int main(int argc, char* argv[]){
        char* fname = argv[1];
        fstream stream(fname, ios::in | ios::binary | ios::ate);
        if (stream.is_open()){
		classFileSize = stream.tellg();
        //cout << size << "\n";
		vector<char> result(classFileSize);
		stream.seekg(0,ios::beg);
		stream.read(&result[0], classFileSize);	
		stream.close();
		cout << "Compiled From: " << fname << "\n";
		parse(result);
	}
}
