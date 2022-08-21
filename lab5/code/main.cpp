#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>


[[nodiscard]] std::array<std::pair<uint64_t, uint64_t>, 5> get_t() {
	std::array<std::pair<uint64_t, uint64_t>, 5> t_usage_t_total;
	std::ifstream reader("/proc/stat");
	assert(reader.is_open());
	std::vector<std::vector<std::string>> table_read;
	{
		std::vector<std::string> this_cpu;
		while (reader.good()) {
			std::string this_string;
			reader >> this_string;
			if (std::all_of(this_string.begin() + 1, this_string.end(), ::isdigit)) {
				this_cpu.push_back(this_string);
			} else {
				if (this_cpu.size() > 0)
					table_read.push_back(this_cpu);
				this_cpu.clear();
				this_cpu.push_back(this_string);
			}
		}

		//Calculation:

		for (size_t i = 0; i < 5; i++) {//for each core
			uint64_t t_total{0}, t_idle{0};
			std::cout << "FOR " << table_read.at(i).at(0) << ":" << std::endl;
			for (size_t j = 1; j < table_read.at(i).size(); j++) {//for each time
				t_total += std::stoll(table_read.at(i).at(j));
				if (j == 3 || j == 4)
					t_idle += std::stoll(table_read.at(i).at(j));
			}
			std::cout
					<< "t_total=" << t_total << " "
					<< "t_idle=" << t_idle << " "
					<< "t_usage=" << t_total - t_idle << std::endl;
			t_usage_t_total.at(i).first = t_total - t_idle;
			t_usage_t_total.at(i).second = t_total;
		}
	}
	reader.close();
	return t_usage_t_total;
}


int main() {
	system("echo ECE 1175 Yinhao Qian Lab5 - Task 2");
	auto t1 = get_t();
	system("ssh pi@yinhao /home/pi/Documents/lab5/task2.sh");
	std::this_thread::sleep_for(std::chrono::seconds(1));;
	auto t2 = get_t();
	for (size_t i = 0; i < 5; i++) {
		std::cout
				<< "======================================\n"
				<< "t_total_2-t_total_1=" << t2.at(i).second - t1.at(i).second<<" "
				<< "t_usage_2-t_usage_1=" << t2.at(i).first - t1.at(i).first<<" "
				<< "%util=" << double(t2.at(i).first - t1.at(i).first) / double (t2.at(i).second - t1.at(i).second)
				<<std::endl;
	}

	return 0;
}