//
// Created by 42kangaroo on 29.12.19.
//

#include "listQuest.hpp"

namespace Lily {
    std::vector<std::shared_ptr<questInterface>> listQuest::sameAnswers;

    listQuest::listQuest() {
        using namespace functions;
        loadDatabase();
        addEllements(weather::getWeather, {"What", "Weather"}, 5);
        addEllements(weather::getWeather, {"How", "Weather"}, 5);
        addEllements(dateSP::getDate, {"What", "Date"}, 5);
        addEllements(timeSP::getTime, {"What", "time"}, 5);
        addEllements(volume_control::setAllVolumeUp, {"Volume", "up"}, 6);
        addEllements(volume_control::setAllVolumeDown, {"Volume", "down"}, 6);
        addEllements(volume_control::setCaptureVolumeUp, {"capture", "Volume", "up"}, 5);
        addEllements(volume_control::setCaptureVolumeDown, {"capture", "Volume", "down"}, 5);
        addEllements(volume_control::setCaptureVolumeDown, {"microphone", "Volume", "down"}, 4);
        addEllements(volume_control::setCaptureVolumeUp, {"microphone", "Volume", "up"}, 4);
        addEllements(volume_control::setPlaybackVolumeUp, {"playback", "Volume", "up"}, 5);
        addEllements(volume_control::setPlaybackVolumeDown, {"playback", "Volume", "down"}, 5);
        addEllements(volume_control::setPlaybackVolumeUp, {"output", "Volume", "up"}, 4);
        addEllements(volume_control::setPlaybackVolumeDown, {"output", "Volume", "down"}, 4);
        addEllements(repeat::repeatWhatSaid, {"Say"}, 2);
        samePriority = static_cast<const std::shared_ptr<questInterface>>(new questFunc(listQuest::getSameAnswers,
                                                                                        {"samePriority"},
                                                                                        99));
    }


    void
    listQuest::addEllements(std::vector<std::string> answer, std::vector<std::string> words, int priority,
                            questType how) {
        try {
            std::shared_ptr<questInterface> wordQuest{
                    std::make_shared<NormalQuestion>(std::move(answer), std::move(words), priority,
                                                     how)};
            if (!doesMakeOtherImpossible(wordQuest)) {
                Dictionary_txt::addToDic(wordQuest->getAsString());
                questList.emplace(wordQuest);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }
    }

    void
    listQuest::addEllements(listQuest::strFunc function, std::vector<std::string> words, int priority, questType how) {
        try {
            std::shared_ptr<questInterface> question{
                    std::make_shared<questFunc>(std::move(function), std::move(words), priority,
                                                how)};
            if (!doesMakeOtherImpossible(question)) {
                Dictionary_txt::addToDic(question->getAsString());
                questList.emplace(question);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }
    }

    void
    listQuest::addEllements(listQuest::strFuncParam function, std::vector<std::string> words, int priority,
                            questType how) {
        try {
            std::shared_ptr<questInterface> answer{
                    std::make_shared<questFuncString>(std::move(function), std::move(words), priority,
                                                      how)};
            if (!doesMakeOtherImpossible(answer)) {
                Dictionary_txt::addToDic(answer->getAsString());
                questList.emplace(answer);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }
    }

    void
    listQuest::addEllements(std::vector<std::string> answer, std::vector<std::string> words, int priority,
                            const std::string &lang,
                            questType how) {
        try {
            std::shared_ptr<questInterface> wordQuest{
                    std::make_shared<NormalQuestion>(std::move(answer), std::move(words), priority, lang,
                                                     how)};
            if (!doesMakeOtherImpossible(wordQuest)) {
                Dictionary_txt::addToDic(wordQuest->getAsString());
                questList.emplace(wordQuest);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }

    }

    void
    listQuest::addEllements(listQuest::strFunc function, std::vector<std::string> words, int priority,
                            const std::string &lang,
                            questType how) {
        try {
            std::shared_ptr<questInterface> question{
                    std::make_shared<questFunc>(std::move(function), std::move(words), priority, lang,
                                                how)};
            if (!doesMakeOtherImpossible(question)) {
                Dictionary_txt::addToDic(question->getAsString());
                questList.emplace(question);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }
    }

    void
    listQuest::addEllements(listQuest::strFuncParam function, std::vector<std::string> words, int priority,
                            const std::string &lang,
                            questType how) {
        try {
            std::shared_ptr<questInterface> answer{
                    std::make_shared<questFuncString>(std::move(function), std::move(words), priority, lang,
                                                      how)};
            if (!doesMakeOtherImpossible(answer)) {
                Dictionary_txt::addToDic(answer->getAsString());
                questList.emplace(answer);
            }
        } catch (std::invalid_argument e) {
            std::cout << e.what() << "\n";
        }
    }

    std::shared_ptr<questInterface>
    listQuest::comparePriotity(const std::shared_ptr<questInterface> &quest1,
                               const std::shared_ptr<questInterface> &quest2) {
        if (*quest1 == *quest2) {
            samePriority->setPriority(quest1->getPriority());
            if (quest1 != samePriority) {
                sameAnswers.push_back(quest1);
            }
            if (quest2 != samePriority) {
                sameAnswers.push_back(quest2);
            }
            return samePriority;
        }
        sameAnswers.clear();
        return (*quest1 < *quest2) ? quest1 : quest2;
    }

    std::string listQuest::getSameAnswers() {
        std::string text = "The questions with the keywords ";
        for (const auto &str : sameAnswers) {
            if (str == sameAnswers.at(sameAnswers.size() - 2)) {
                text += "'" + str->getAsString() + "' and ";
            } else if (str == sameAnswers.back()) {
                text += "'" + str->getAsString() + "' ";
            } else {
                text += "'" + str->getAsString() + "', ";
            }
        }
        text += "have the same Priority";
        return text;
    }


    std::string listQuest::getAnswer(const std::string &question) {
        std::shared_ptr<questInterface> quest = samePriority;
        bool changed = false;
        it = questList.begin();
        while (it != questList.end()) {
            if (*(*it) <= *quest) {
                if ((*it)->getWords().size() < 2 && (*it)->getQuestType() == questType::IS) {
                    if (QString::fromStdString((*it)->getWords().at(0)).compare(
                            QString::fromStdString(question),
                            Qt::CaseInsensitive) == 0) {
                        quest = comparePriotity(quest, *it);
                        changed = true;
                    }
                } else {
                    int has = 0;
                    for (auto &str : (*it)->getWords()) {
                        if (!QString::fromStdString(question).contains(QString::fromStdString(str),
                                                                       Qt::CaseInsensitive)) {
                            break;
                        } else {
                            has++;
                        }
                    }
                    if (has == (*it)->getWords().size()) {
                        quest = comparePriotity(quest, *it);
                        changed = true;
                    }
                }
                it++;
            } else {
                break;
            }
        }
        return (changed) ? quest->getAnswer(question) + "(lang:" + quest->getLang() + ")"
                         : "no answer found(lang:mb-en1)";
    }

    void listQuest::loadDatabase() {
        QSqlQueryModel model;
        model.setQuery("select * from questions order by priority, question;");
        for (int i = 0; i < model.rowCount(); ++i) {
            int priority = model.record(i).value("priority").toInt();
            std::vector<std::string> answer = std::move(String2Vector(
                    model.record(i).value("answer").toString().toStdString()));
            std::vector<std::string> words = std::move(String2Vector(
                    model.record(i).value("question").toString().toStdString()));
            questType questType = (model.record(i).value("questionType").toString() == "has") ? questType::HAS
                                                                                              : questType::IS;
            std::string language = model.record(i).value("language").toString().toStdString();
            addEllements(answer, words, priority, language, questType);
        }
    }

    std::vector<std::string> listQuest::String2Vector(const std::string &inputSting) {
        std::vector<QString> qResult = QString(inputSting.c_str()).split(",").toVector().toStdVector();
        std::vector<std::string> result;
        for (const QString &qStr : qResult) {
            result.push_back(qStr.simplified().toStdString());
        }
        return result;
    }

    bool listQuest::doesMakeOtherImpossible(std::shared_ptr<questInterface> quest) {
        for (auto questOld : questList) {
            int number = 0;
            for (const auto &word : questOld->getWords()) {
                for (const auto &word2 : quest->getWords()) {
                    if (QString::fromStdString(word).contains(QString::fromStdString(word2), Qt::CaseInsensitive) ||
                        QString::fromStdString(word2).contains(QString::fromStdString(word), Qt::CaseInsensitive)) {
                        number++;
                    }
                }
            }
            std::shared_ptr<questInterface> longer{
                    (questOld->getWords().size() < quest->getWords().size()) ? quest : questOld};
            if ((*quest > *questOld && (number > questOld->getWords().size() || number >= longer->getWords().size())) ||
                (*quest < *questOld && (number > quest->getWords().size() || number >= longer->getWords().size())) ||
                (*quest == *questOld &&
                 (number > quest->getWords().size() || number > questOld->getWords().size() ||
                  number >= longer->getWords().size()))) {
                std::shared_ptr<questInterface> bigger = (quest->getWords().size() < questOld->getWords().size())
                                                         ? quest
                                                         : questOld;
                std::shared_ptr<questInterface> litteler = (quest->getWords().size() < questOld->getWords().size())
                                                           ? questOld
                                                           : quest;
                std::cout << "warning: the question with the keywords \"" << bigger->getAsString()
                          << "\" makes question with keywords \""
                          << litteler->getAsString() << "\" impossible" << std::endl;
                if (bigger == quest) {
                    Dictionary_txt::addToDic(quest->getAsString());
                }
                questList.erase(questOld);
                questList.emplace(bigger);
                return true;
            }
        }
        return false;
    }
}



