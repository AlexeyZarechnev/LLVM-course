#include <fstream>
#include <ios>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

std::map<std::vector<std::string>, std::size_t> stats;
std::vector<std::string> instructions;

void analyzePatternsOfLength(int patternLen) {
    for (size_t i = 0; i <= instructions.size() - patternLen; ++i) {
        std::vector<std::string> pattern(
            instructions.begin() + i,
            instructions.begin() + i + patternLen
        );
        stats[pattern]++;
    }
}

void analyzePatterns(int maxPatternLength = 5) {
    stats.clear();
    
    for (int patternLen = 1; patternLen <= maxPatternLength; ++patternLen) {
        analyzePatternsOfLength(patternLen);
    }
}

void printTopPatterns(std::ofstream& stream, size_t topN = 10) {
    std::vector<std::pair<std::vector<std::string>, size_t>> sortedPatterns(
        stats.begin(), stats.end()
    );
    
    std::sort(sortedPatterns.begin(), sortedPatterns.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    
    stream << "=== Top " << topN << " Instruction Patterns ===\n";
    for (size_t i = 0; i < std::min(topN, sortedPatterns.size()); ++i) {
        const auto& pattern = sortedPatterns[i].first;
        size_t count = sortedPatterns[i].second;
        
        stream << "Pattern " << (i + 1) << ": [\n";
        for (size_t j = 0; j < pattern.size(); ++j) {
            stream << "  " << pattern[j] << '\n';
        }
        stream << "] - Count: " << count << "\n";
    }
}

int main(int argc, char** argv) {
    std::ifstream trace(argv[1]);
    std::string instruction;
    while (!trace.eof()) {
        std::getline(trace, instruction);
        instructions.push_back(instruction);
    }

    analyzePatterns();
    std::ofstream out(argv[2], std::ios_base::out | std::ios_base::trunc);
    printTopPatterns(out);

}