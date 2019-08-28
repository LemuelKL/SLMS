#include "category.h"

QStringList Category::internal_holder_ =
{
    "Uncategorized",
    "Action And Adventure",
    "Alternate History",
    "Anthology",
    "Chick Lit",
    "Children's Literature",
    "Comic Book",
    "Coming Of Age",
    "Crime",
    "Drama",
    "Fairytale",
    "Fantasy",
    "Graphic Novel",
    "Historical Fiction",
    "Horror",
    "Mystery",
    "Paranormal Romance",
    "Picture Book",
    "Poetry",
    "Political Thriller",
    "Romance",
    "Satire",
    "Science Fiction",
    "Short Story",
    "Suspense",
    "Thriller",
    "Young Adult"
};

Category::Category()
{

}

int Category::count_ = internal_holder_.length();

QStringList Category::AllCategoryStrings()
{
    return internal_holder_;
}

QString Category::EnumToString(Category::ENUM en)
{
    return internal_holder_.at(en);
}

QString Category::EnumToString(int en)
{
    return internal_holder_.at(en);
}

Category::ENUM Category::StringToEnum(QString str)
{
    for (int ret = 0; ret < internal_holder_.size(); ret++)
    {
        if (internal_holder_.at(ret) == str)
            return static_cast<ENUM>(ret);
    }
    return Category::ENUM::UNCATEGORIZED;
}
