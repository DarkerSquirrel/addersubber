#include "LogicGates.hpp"
#include <string>


struct fulladder_struct
{
	bool sum;
	bool cout;

	fulladder_struct(bool sum, bool cout) : sum(sum), cout(cout) {};

};

struct subtractor_struct
{
	bool diff;
	bool borr;

	subtractor_struct(bool diff, bool borr) : diff(diff), borr(borr) {};

};



fulladder_struct fulladder(bool inp_a, bool inp_b, bool inp_c)
{
	bool outp_d = LogicGates(inp_b, inp_c).XOR();
	bool outp_e = LogicGates(inp_b, inp_c).AND();
	bool outp_f = LogicGates(outp_d, inp_a).AND();
	bool outp_g = LogicGates(outp_f, outp_e).OR(); //cout
	bool outp_h = LogicGates(inp_a, outp_d).XOR(); //sum

	return fulladder_struct(outp_h, outp_g);

}


fulladder_struct halfadder(bool inp_a, bool inp_b)
{
	bool outp_sum = LogicGates(inp_a, inp_b).XOR();
	bool outp_cout = LogicGates(inp_a, inp_b).AND();

	return fulladder_struct(outp_sum, outp_cout);
}

std::string anybit_fulladder(std::string inp1, std::string inp2, int max_bits)
{


	if (inp1.length() != max_bits && inp2.length() != max_bits)
	{
		//pad at least one of them
		int difference = max_bits - inp2.length();


		std::string res = [difference, inp2]() {
			std::string ret = "";
			std::string new_ret = "";
			for (int i = inp2.length() - 1; i >= 0; i--)
				ret += inp2[i];


			for (int i = 0; i <= difference - 1; i++)
				ret += "0";

			for (int i = ret.length() - 1; i >= 0; i--)
				new_ret += ret[i];


			return new_ret;
		}();
		inp2 = res;
	}

	if (inp1.length() > inp2.length() || inp1.length() < inp2.length())
	{
		[&inp1, &inp2]()
		{

			if (inp1.length() > inp2.length()) {
				//inp1 is longer than inp2
				//get the length of inp1 and find the difference between them
				int difference = inp1.length() - inp2.length();

				//pad the start with 0's of the shorter string

				std::string res = [difference, inp2]() {
					std::string ret = "";
					std::string new_ret = "";
					for (int i = inp2.length() - 1; i >= 0; i--)
						ret += inp2[i];

					//std::printf("Reversed inp2 : %s\n", ret.c_str());

					for (int i = 0; i <= difference - 1; i++)
						ret += "0";

					//std::printf("Reversed inp2 with added padding : %s\n", ret.c_str());

					for (int i = ret.length() - 1; i >= 0; i--)
						new_ret += ret[i];

					//std::printf("reversed again : %s\n", new_ret.c_str());

					return new_ret;
				}();
				inp2 = res;


			}

			else if (inp2.length() > inp1.length()) {
				//inp2 is longer than inp1
				//get the length of inp2 and find the difference between them
				int difference = inp2.length() - inp1.length();

				//pad the start with 0's of the shorter string

				std::string res = [difference, inp1]() {
					std::string ret = "";
					std::string new_ret = "";
					for (int i = inp1.length() - 1; i >= 0; i--)
						ret += inp1[i];


					for (int i = 0; i <= difference - 1; i++)
						ret += "0";


					for (int i = ret.length() - 1; i >= 0; i--)
						new_ret += ret[i];


					return new_ret;
				}();
				inp1 = res;
			}
		}();



	}


	std::string ret = "";
	fulladder_struct* prevResult = new fulladder_struct(0, 0);
	for (int i = max_bits - 1; i >= 0; i--)
	{
		fulladder_struct currRes = fulladder(static_cast<int>(inp1[i]) - 48, static_cast<int>(inp2[i]) - 48, prevResult->cout);
		ret += std::to_string(currRes.sum);
		*prevResult = currRes;

	}

	ret += std::to_string(prevResult->cout);


	return [ret]() {
		std::string new_ret = "";
		for (int i = ret.length() - 1; i >= 0; i--)
			new_ret += ret[i];

		return new_ret;
	}();

}


subtractor_struct haldsubtractor(bool inp_a, bool inp_b)
{
	bool outp_diff = LogicGates(inp_a, inp_b).XOR();
	bool outp_borr = LogicGates(LogicGates(inp_a, 0).NOT(), inp_b).AND();

	return subtractor_struct(outp_diff, outp_borr);
}

subtractor_struct fullsubtractor(bool inp_a, bool inp_b, bool inp_c)
{
	bool outp_d = LogicGates(inp_a, inp_b).XOR();
	bool outp_e = LogicGates(LogicGates(inp_a, 0).NOT(), inp_b).AND();
	bool outp_f = LogicGates(inp_c, LogicGates(outp_d, 0).NOT()).AND();
	bool outp_g = LogicGates(inp_c, outp_d).XOR(); //diff
	bool outp_h = LogicGates(outp_f, outp_e).OR(); //b out

	return subtractor_struct(outp_g, outp_h);
}


std::string anybit_subtractor(std::string inp1, std::string inp2, int max_bits)
{


	if (inp1.length() != max_bits && inp2.length() != max_bits)
	{
		//pad at least one of them
		int difference = max_bits - inp2.length();


		std::string res = [difference, inp2]() {
			std::string ret = "";
			std::string new_ret = "";
			for (int i = inp2.length() - 1; i >= 0; i--)
				ret += inp2[i];


			for (int i = 0; i <= difference - 1; i++)
				ret += "0";

			for (int i = ret.length() - 1; i >= 0; i--)
				new_ret += ret[i];


			return new_ret;
		}();
		inp2 = res;
	}

	if (inp1.length() > inp2.length() || inp1.length() < inp2.length())
	{
		[&inp1, &inp2]()
		{

			if (inp1.length() > inp2.length()) {
				//inp1 is longer than inp2
				//get the length of inp1 and find the difference between them
				int difference = inp1.length() - inp2.length();

				//pad the start with 0's of the shorter string

				std::string res = [difference, inp2]() {
					std::string ret = "";
					std::string new_ret = "";
					for (int i = inp2.length() - 1; i >= 0; i--)
						ret += inp2[i];

					//std::printf("Reversed inp2 : %s\n", ret.c_str());

					for (int i = 0; i <= difference - 1; i++)
						ret += "0";

					//std::printf("Reversed inp2 with added padding : %s\n", ret.c_str());

					for (int i = ret.length() - 1; i >= 0; i--)
						new_ret += ret[i];

					//std::printf("reversed again : %s\n", new_ret.c_str());

					return new_ret;
				}();
				inp2 = res;


			}

			else if (inp2.length() > inp1.length()) {
				//inp2 is longer than inp1
				//get the length of inp2 and find the difference between them
				int difference = inp2.length() - inp1.length();

				//pad the start with 0's of the shorter string

				std::string res = [difference, inp1]() {
					std::string ret = "";
					std::string new_ret = "";
					for (int i = inp1.length() - 1; i >= 0; i--)
						ret += inp1[i];


					for (int i = 0; i <= difference - 1; i++)
						ret += "0";


					for (int i = ret.length() - 1; i >= 0; i--)
						new_ret += ret[i];


					return new_ret;
				}();
				inp1 = res;
			}
		}();



	}

	bool isinp1Bigger = [inp1,inp2]()
	{
		int inp1_int = [inp1]() {
			std::string res = [inp1]() {
				std::string new_ret = "";
				for (int i = inp1.length() - 1; i >= 0; i--)
					new_ret += inp1[i];

				return new_ret;
			}();
			int total = 0;
			for (int i = res.length() - 1; i >= 0; i--)
			{
				if ((static_cast<int>(res[i]) - 48) == 1)
				{
					total += pow(2, i);
				}
			}
			return total;
		}();

		int inp2_int = [inp2]() {
			std::string res = [inp2]() {
				std::string new_ret = "";
				for (int i = inp2.length() - 1; i >= 0; i--)
					new_ret += inp2[i];

				return new_ret;
			}();
			int total = 0;
			for (int i = res.length() - 1; i >= 0; i--)
			{
				if ((static_cast<int>(res[i]) - 48) == 1)
				{
					total += pow(2, i);
				}
			}
			return total;
		}();

		return inp1_int > inp2_int;
	}();

	std::string ret = "";
	subtractor_struct* prevResult = new subtractor_struct(0, 0);
	for (int i = max_bits - 1; i >= 0; i--)
	{
		subtractor_struct currRes = subtractor_struct(0,0);
		if(isinp1Bigger)
			currRes = fullsubtractor(static_cast<int>(inp1[i]) - 48, static_cast<int>(inp2[i]) - 48, prevResult->borr);
		else
			currRes = fullsubtractor(static_cast<int>(inp2[i]) - 48, static_cast<int>(inp1[i]) - 48, prevResult->borr);
		
		ret += std::to_string(currRes.diff);
		*prevResult = currRes;

	}

	ret += std::to_string(prevResult->borr);


	return [ret, isinp1Bigger]() {
		std::string new_ret = "";
		if (!isinp1Bigger)
			new_ret += "-";
		for (int i = ret.length() - 1; i >= 0; i--)
			new_ret += ret[i];

		return new_ret;
	}();

}



INT main()
{
	fulladder_struct halfadderop_1 = halfadder(0, 0);
	fulladder_struct halfadderop_2 = halfadder(1, 0);
	fulladder_struct halfadderop_3 = halfadder(0, 1);
	fulladder_struct halfadderop_4 = halfadder(1, 1);
	//half adder operations
	std::printf("%d : %d\n%d : %d\n%d : %d\n%d : %d\n",
		halfadderop_1.sum, halfadderop_1.cout,
		halfadderop_2.sum, halfadderop_2.cout,
		halfadderop_3.sum, halfadderop_3.cout,
		halfadderop_4.sum, halfadderop_4.cout
	);
	system("CLS");

	//full adder operations

	fulladder_struct fulladderop_1 = fulladder(0, 0, 0);
	fulladder_struct fulladderop_2 = fulladder(0, 0, 1);
	fulladder_struct fulladderop_3 = fulladder(1, 0, 0);
	fulladder_struct fulladderop_4 = fulladder(1, 0, 1);
	fulladder_struct fulladderop_5 = fulladder(0, 1, 0);
	fulladder_struct fulladderop_6 = fulladder(0, 1, 1);
	fulladder_struct fulladderop_7 = fulladder(1, 1, 0);
	fulladder_struct fulladderop_8 = fulladder(1, 1, 1);

	std::printf("%d : %d\n%d : %d\n%d : %d\n%d : %d\n%d : %d\n%d : %d\n%d : %d\n%d : %d\n",
		fulladderop_1.sum, halfadderop_1.cout,
		fulladderop_2.sum, fulladderop_2.cout,
		fulladderop_3.sum, fulladderop_3.cout,
		fulladderop_4.sum, fulladderop_4.cout,
		fulladderop_5.sum, fulladderop_5.cout,
		fulladderop_6.sum, fulladderop_6.cout,
		fulladderop_7.sum, fulladderop_7.cout,
		fulladderop_8.sum, fulladderop_8.cout
	);
	system("CLS");

	//full adder operations 2
	std::string operation_1 = anybit_fulladder("0010", "1001", 4);
	std::string operation_2 = anybit_fulladder("1000", "0110", 4);
	std::string operation_3 = anybit_fulladder("0110", "0101", 4);
	std::string operation_4 = anybit_fulladder("0001", "0111", 4);

	std::printf("%s\n%s\n%s\n%s", 
		operation_1.c_str(),
		operation_2.c_str(),
		operation_3.c_str(),
		operation_4.c_str()
	);
	system("CLS");

	//half subtractor operations
	subtractor_struct soperation_1 = haldsubtractor(0, 0);
	subtractor_struct soperation_2 = haldsubtractor(1, 0);
	subtractor_struct soperation_3 = haldsubtractor(0, 1);
	subtractor_struct soperation_4 = haldsubtractor(1, 1);
	std::printf("%d : %d\n%d : %d\n%d : %d\n%d : %d\n",
		soperation_1.diff, soperation_1.borr,
		soperation_2.diff, soperation_2.borr,
		soperation_3.diff, soperation_3.borr,
		soperation_4.diff, soperation_4.borr
	);
	system("CLS");
	//anybit_subtractor
	std::string s_operation_1 = anybit_subtractor("0010", "1001", 4);
	std::string s_operation_2 = anybit_subtractor("1000", "0110", 4);
	std::string s_operation_3 = anybit_subtractor("0110", "0101", 4);
	std::string s_operation_4 = anybit_subtractor("1001", "0111", 4);


	std::printf("%s\n%s\n%s\n%s",
		s_operation_1.c_str(),
		s_operation_2.c_str(),
		s_operation_3.c_str(),
		s_operation_4.c_str()
	);

	

	for (;;) {}
	return 0;
}