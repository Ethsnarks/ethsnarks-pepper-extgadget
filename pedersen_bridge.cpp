#include "common.cpp"
#include "jubjub/pedersen_hash.hpp"

using ethsnarks::ppT;
using ethsnarks::VariableArrayT;
using ethsnarks::ProtoboardT;
using ethsnarks::jubjub::PedersenHash;
using ethsnarks::jubjub::Params;

#define BUFLEN 10240

#define LEFT_INPUT_SIZE 254
#define RIGHT_INPUT_SIZE 254
#define OUTPUT_SIZE 2

uint64_t inputSize() {
	return LEFT_INPUT_SIZE + RIGHT_INPUT_SIZE;
}

uint64_t outputSize() {
	return OUTPUT_SIZE;
}

ProtoboardT getProtoboard(const char* assignment)
{
    ppT::init_public_params();
    ProtoboardT pb;

    VariableArrayT input_data;
    input_data.allocate(pb, inputSize(), FMT("annotation_prefix", " scaler to multiply by"));
    

    Params params; 
    PedersenHash f(pb, params, "PedersenHash", input_data, "the_gadget");
    f.generate_r1cs_constraints();

	if (assignment) {
		libff::bit_vector input_bv;
     		for (int i = 0; i < inputSize(); i++) {
        		input_bv.push_back(assignment[2*i] - '0');
    		}
		input_data.fill_with_bits(pb, input_bv);

     		f.generate_r1cs_witness();
		assert(pb.is_satisfied());
	}
    
    return pb;
}
