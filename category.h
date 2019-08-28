#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QStringList>

class Category
{
public:
    Category();

    enum ENUM
    {
        UNCATEGORIZED = 0,
        ACTION_AND_ADVENTURE = 1,
        ALTERNATE_HISTORY = 2,
        ANTHOLOGY = 3,
        CHICK_LIT = 4,
        CHILDRENS_LITERATURE = 5,
        COMIC_BOOK = 6,
        COMING_OF_AGE = 7,
        CRIME = 8,
        DRAMA = 9,
        FAIRYTALE = 10,
        FANTASY = 11,
        GRAPHIC_NOVEL = 12,
        HISTORICAL_FICTION = 13,
        HORROR = 14,
        MYSTERY = 15,
        PARANORMAL_ROMANCE = 16,
        PICTURE_BOOK = 17,
        POETRY = 18,
        POLITICAL_THRILLER = 19,
        ROMANCE = 20,
        SATIRE = 21,
        SCIENCE_FICTION = 22,
        SHORT_STORY = 23,
        SUSPENSE = 24,
        THRILLER = 25,
        YOUNG_ADULT = 26
    };

    static int count_;

    static QStringList AllCategoryStrings();
    static QString EnumToString(Category::ENUM);
    static QString EnumToString(int);
    static Category::ENUM StringToEnum(QString str);

private:
    static QStringList internal_holder_;
};

#endif // CATEGORY_H
