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

private:
    int id;
    int dzial_id;
    int rozdzial_id;
    std::string pytanie;
};

#endif
