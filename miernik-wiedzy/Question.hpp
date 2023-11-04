#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>

class Question {
public:
    Question(int id, int dzial_id, int rozdzial_id, const std::string& pytanie);

    int getId() const;
    int getSectionId() const;
    int getChapterId() const;
    const std::string& getContent() const;
    const std::string& getCorrectAnswer() const;

private:
    int id;
    int dzial_id;
    int rozdzial_id;
    std::string pytanie;
    std::string poprawna_odpowiedz;
};

#endif
