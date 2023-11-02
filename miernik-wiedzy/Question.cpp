#include "Question.hpp"

Question::Question(int id, int dzial_id, int rozdzial_id, const std::string& pytanie)
    : id(id), pytanie(pytanie), dzial_id(dzial_id), rozdzial_id(rozdzial_id) {}

int Question::getId() const {
    return id;
}

int Question::getSectionId() const {
    return dzial_id;
}

int Question::getChapterId() const {
    return rozdzial_id;
}

const std::string& Question::getContent() const {
    return pytanie;
}
