#include <iostream>

#include "common.h"

using namespace libsnark;
using ethsnarks::FieldT;
using ethsnarks::ppT;
using ethsnarks::ProtoboardT;

void constraint_to_json(linear_combination<FieldT>& constraints, std::stringstream &ss)
{
    ss << "{";
    uint count = 0;
    for (const auto& lt : constraints.terms)
    {
		if (lt.coeff == 0) {
            continue;
        } 
        if (count != 0) {
            ss << ",";
        }
        
        ss << '"' << lt.index << '"' << ":" << '"' << lt.coeff.as_bigint() << '"';
        count++;
    }
    ss << "}";
}

std::string r1cs_to_json(ProtoboardT& pb)
{
    auto constraints = pb.get_constraint_system();
    std::stringstream ss;
    for (size_t c = 0; c < constraints.num_constraints(); ++c)
    {
        ss << "[";// << "\"A\"=";
        constraint_to_json(constraints.constraints[c].a, ss);
        ss << ",";// << "\"B\"=";
        constraint_to_json(constraints.constraints[c].b, ss);
        ss << ",";// << "\"C\"=";;
        constraint_to_json(constraints.constraints[c].c, ss);
    	ss << "]\n";
    }
    ss.rdbuf()->pubseekpos(0, std::ios_base::out);
    return ss.str();
}

std::string witness_to_json(ProtoboardT& pb) {
	auto values = pb.full_variable_assignment();
	std::stringstream ss;
	for (size_t i = 0; i < values.size(); ++i) {
		ss << values[i].as_bigint() << " ";
	}
	return ss.str();
}

int main(int argc, char **argv) 
{ 
    	ppT::init_public_params();

	if (argc != 2) {
		std::cout << "Needs to be called with a command.\n";
		return 1;
	}

	if (strcmp("size", argv[1]) == 0) {
		auto pb = getProtoboard(nullptr);
		std::cout << (pb.num_variables() - inputSize() - outputSize()) << "\n";
	} else if (strcmp("constraints", argv[1]) == 0) {
		auto pb = getProtoboard(nullptr);
		std::cout << r1cs_to_json(pb);
	} else if (strcmp("witness", argv[1]) == 0) {
		std::string input_line;
		std::getline(std::cin, input_line);
		auto pb = getProtoboard(input_line.c_str());
		std::cout << witness_to_json(pb);
	} else {
		std::cout << "Unknown command `" << argv[1] << "`! Expecting size, constraints or witness.\n";
		return 1;
	}
    return 0; 
} 
