#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;
using Vocabulary = std::unordered_map<std::string, int>;
using Sentence = std::vector<std::string>;

Vector add(const Vector& left, const Vector& right) {
    if (left.size() != right.size()) {
        throw std::runtime_error("vectors must have the same size");
    }

    Vector result;
    result.reserve(left.size());
    for (std::size_t i = 0; i < left.size(); ++i) {
        result.push_back(left[i] + right[i]);
    }
    return result;
}

void print_vector(const Vector& vector) {
    std::cout << "[";
    for (std::size_t i = 0; i < vector.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << vector[i];
    }
    std::cout << "]";
}

std::string join_sentence(const Sentence& sentence) {
    std::string result;
    for (std::size_t i = 0; i < sentence.size(); ++i) {
        if (i > 0) {
            result += " ";
        }
        result += sentence[i];
    }
    return result;
}

int token_id_for(const Vocabulary& vocab, const std::string& token) {
    const auto it = vocab.find(token);
    if (it == vocab.end()) {
        throw std::runtime_error("unknown token: " + token);
    }
    return it->second;
}

void print_sequence(
    const std::string& label,
    const Sentence& sentence,
    const Matrix& token_embeddings,
    const Matrix& positional_embeddings,
    const Vocabulary& vocab) {
    std::cout << label << ": " << join_sentence(sentence) << "\n";

    for (std::size_t position = 0; position < sentence.size(); ++position) {
        const std::string& token = sentence[position];
        const int token_id = token_id_for(vocab, token);

        if (static_cast<std::size_t>(token_id) >= token_embeddings.size()) {
            throw std::runtime_error("token id out of range");
        }
        if (position >= positional_embeddings.size()) {
            throw std::runtime_error("position out of range");
        }

        const Vector& token_embedding = token_embeddings[static_cast<std::size_t>(token_id)];
        const Vector& positional_embedding = positional_embeddings[position];
        const Vector final_input_vector = add(token_embedding, positional_embedding);

        std::cout << "position " << position << " token '" << token << "'\n";
        std::cout << "  token embedding:    ";
        print_vector(token_embedding);
        std::cout << "\n";
        std::cout << "  position embedding: ";
        print_vector(positional_embedding);
        std::cout << "\n";
        std::cout << "  final input vector: ";
        print_vector(final_input_vector);
        std::cout << "\n\n";
    }
}

int main() {
    const Vocabulary vocab = {
        {"dog", 0},
        {"bites", 1},
        {"man", 2},
    };

    const Matrix token_embeddings = {
        {1.00, 0.20, -0.10, 0.50},  // dog
        {0.10, 1.20, 0.30, -0.40},  // bites
        {0.90, -0.30, 0.80, 0.10},  // man
    };

    const Matrix positional_embeddings = {
        {0.01, 0.02, 0.03, 0.04},       // P(0)
        {0.10, 0.20, 0.30, 0.40},       // P(1)
        {-0.05, -0.10, -0.15, -0.20},  // P(2)
    };

    const Sentence sentence_a = {"dog", "bites", "man"};
    const Sentence sentence_b = {"man", "bites", "dog"};

    std::cout << std::fixed << std::setprecision(2);

    print_sequence("Sentence A", sentence_a, token_embeddings, positional_embeddings, vocab);
    print_sequence("Sentence B", sentence_b, token_embeddings, positional_embeddings, vocab);

    const Vector dog_embedding = token_embeddings[static_cast<std::size_t>(token_id_for(vocab, "dog"))];
    const Vector dog_at_position_0 = add(dog_embedding, positional_embeddings[0]);
    const Vector dog_at_position_2 = add(dog_embedding, positional_embeddings[2]);

    std::cout << "Observation\n";
    std::cout << "- The token embedding for `dog` is always the same: ";
    print_vector(dog_embedding);
    std::cout << "\n";
    std::cout << "- Final vector for `dog` at position 0: ";
    print_vector(dog_at_position_0);
    std::cout << "\n";
    std::cout << "- Final vector for `dog` at position 2: ";
    print_vector(dog_at_position_2);
    std::cout << "\n";
    std::cout << "- Therefore the model can distinguish `dog at position 0` "
              << "from `dog at position 2`.\n";

    return 0;
}
