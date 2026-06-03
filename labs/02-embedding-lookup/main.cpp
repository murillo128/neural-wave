#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct TokenEmbedding {
    std::string token;
    std::vector<double> vector;
};

using Vocabulary = std::vector<TokenEmbedding>;
using TokenToId = std::unordered_map<std::string, int>;

TokenToId build_token_to_id(const Vocabulary& vocabulary) {
    TokenToId token_to_id;
    for (std::size_t i = 0; i < vocabulary.size(); ++i) {
        token_to_id[vocabulary[i].token] = static_cast<int>(i);
    }
    return token_to_id;
}

int token_id_for(const TokenToId& token_to_id, const std::string& token) {
    const auto it = token_to_id.find(token);
    if (it == token_to_id.end()) {
        throw std::runtime_error("unknown token: " + token);
    }
    return it->second;
}

const std::vector<double>& embedding_for_id(const Vocabulary& vocabulary, int token_id) {
    if (token_id < 0 || static_cast<std::size_t>(token_id) >= vocabulary.size()) {
        throw std::runtime_error("token id out of range");
    }
    return vocabulary[static_cast<std::size_t>(token_id)].vector;
}

double dot_product(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("vectors must have the same size");
    }

    double result = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

double norm(const std::vector<double>& vector) {
    return std::sqrt(dot_product(vector, vector));
}

double cosine_similarity(const std::vector<double>& a, const std::vector<double>& b) {
    const double denominator = norm(a) * norm(b);
    if (denominator == 0.0) {
        throw std::runtime_error("cosine similarity is undefined for zero vectors");
    }
    return dot_product(a, b) / denominator;
}

std::vector<std::pair<std::string, double>> nearest_neighbors(
    const Vocabulary& vocabulary,
    const std::string& query_token,
    const TokenToId& token_to_id,
    int count) {
    const int query_id = token_id_for(token_to_id, query_token);
    const auto& query_vector = embedding_for_id(vocabulary, query_id);

    std::vector<std::pair<std::string, double>> neighbors;
    for (std::size_t i = 0; i < vocabulary.size(); ++i) {
        if (static_cast<int>(i) == query_id) {
            continue;
        }

        neighbors.push_back({
            vocabulary[i].token,
            cosine_similarity(query_vector, vocabulary[i].vector),
        });
    }

    std::sort(neighbors.begin(), neighbors.end(), [](const auto& left, const auto& right) {
        return left.second > right.second;
    });

    if (static_cast<std::size_t>(count) < neighbors.size()) {
        neighbors.resize(static_cast<std::size_t>(count));
    }
    return neighbors;
}

void print_vector(const std::vector<double>& vector) {
    std::cout << "[";
    for (std::size_t i = 0; i < vector.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << vector[i];
    }
    std::cout << "]";
}

void print_lookup(const Vocabulary& vocabulary, const TokenToId& token_to_id, const std::string& token) {
    const int token_id = token_id_for(token_to_id, token);
    const auto& embedding = embedding_for_id(vocabulary, token_id);

    std::cout << "token \"" << token << "\" -> id " << token_id << " -> ";
    print_vector(embedding);
    std::cout << "\n";
}

void print_cosine(
    const Vocabulary& vocabulary,
    const TokenToId& token_to_id,
    const std::string& left,
    const std::string& right) {
    const auto& left_vector = embedding_for_id(vocabulary, token_id_for(token_to_id, left));
    const auto& right_vector = embedding_for_id(vocabulary, token_id_for(token_to_id, right));

    std::cout << "cosine(" << left << ", " << right << ") = "
              << cosine_similarity(left_vector, right_vector) << "\n";
}

void print_neighbors(const Vocabulary& vocabulary, const TokenToId& token_to_id, const std::string& token) {
    std::cout << "nearest neighbors for " << token << ":\n";
    for (const auto& neighbor : nearest_neighbors(vocabulary, token, token_to_id, 3)) {
        std::cout << "  " << neighbor.first << " (cosine = " << neighbor.second << ")\n";
    }
}

int main() {
    // These tiny 3D vectors are manually chosen for this lab. They are not learned.
    // Real model embeddings are learned during training and usually have hundreds or
    // thousands of dimensions.
    const Vocabulary vocabulary = {
        {"cat", {0.95, 0.30, 0.05}},
        {"gato", {0.93, 0.33, 0.06}},
        {"dog", {0.90, 0.36, 0.04}},
        {"house", {-0.20, 0.10, 0.97}},
        {"std", {0.05, 0.95, 0.30}},
        {"vector", {0.04, 0.98, 0.25}},
        {"int", {0.08, 0.92, 0.32}},
        {"string", {0.03, 0.90, 0.38}},
    };

    const TokenToId token_to_id = build_token_to_id(vocabulary);

    std::cout << std::fixed << std::setprecision(4);

    std::cout << "Embedding lookup examples\n";
    std::cout << "Educational point: IDs are arbitrary; vectors carry useful relationships.\n\n";
    print_lookup(vocabulary, token_to_id, "cat");
    print_lookup(vocabulary, token_to_id, "vector");
    print_lookup(vocabulary, token_to_id, "house");

    std::cout << "\nCosine similarities\n";
    print_cosine(vocabulary, token_to_id, "cat", "gato");
    print_cosine(vocabulary, token_to_id, "cat", "dog");
    print_cosine(vocabulary, token_to_id, "cat", "house");
    print_cosine(vocabulary, token_to_id, "vector", "int");
    print_cosine(vocabulary, token_to_id, "std", "vector");
    print_cosine(vocabulary, token_to_id, "vector", "string");

    std::cout << "\nNearest neighbors\n";
    print_neighbors(vocabulary, token_to_id, "cat");
    print_neighbors(vocabulary, token_to_id, "vector");

    return 0;
}
