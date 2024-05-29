#include "comparisor.hpp"

pair<int, int> find_most_similar(const vector<string>& texts) {
	vector<Suffix_tree*> trees;
	Suffix_tree* tree;
	for (const string& text : texts) {
		tree = new Suffix_tree(text);
		trees.push_back(tree);
	}

	double max_similarity = -1.0;
	pair<int, int> most_similar_pair;

	for (size_t i = 0; i < trees.size(); ++i) {
		for (size_t j = i + 1; j < trees.size(); ++j) {
			double similarity = *trees[i] == *trees[j];
			if (similarity > max_similarity) {
				max_similarity = similarity;
				most_similar_pair = { i, j };
			}
		}
	}

	return most_similar_pair;
}