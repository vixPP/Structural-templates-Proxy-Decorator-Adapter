#include <iostream>
#include <string>
//#include <algorithm>
//#include <vector>


class Text
{
public:
    virtual void render(const std::string& data) const
    {
        std::cout << data;
    }

    virtual ~Text() = default;
};

class DecoratedText : public Text
{
public:
    explicit DecoratedText(Text* text) : text_(text){}
    Text* text_;

    virtual ~DecoratedText() = default;
};

class BoldText : public DecoratedText
{
public:
    explicit BoldText(Text* text) : DecoratedText(text) {};
    void render(const std::string& data) 
    const override
    {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }

};

class Paragraph : DecoratedText
{
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {};
    void render(const std::string& data)
    const override
    {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : DecoratedText
{
public:
    explicit Reversed(Text* text) : DecoratedText(text) {};
    void render(const std::string& data)
    const override
    {
        std::string reverse_data = data;
        std::reverse(reverse_data.begin(), reverse_data.end());
        text_->render(reverse_data);

    }
};

class Link 
{
public:
    explicit Link(Text* text) : text_(text) {};
    Text* text_;

    void render(const std::string url, std::string data)
    const 
    {
        std::cout << "<a href = \"" << url << "\">" << data << "</a>";
    }

};


int main()
{
    std::cout << "BoldText: ";
    auto textBlock1{ new BoldText(new Text()) };
    textBlock1->render("Hello World");

    std::cout << std::endl << std::endl << "Paragraph: ";
    auto textBlock2{ new Paragraph(new Text()) };
    textBlock2->render("Hello World");

    std::cout << std::endl << std::endl << "Reversed: ";
    auto textBlock3{ new Reversed(new Text()) };
    textBlock3->render("Hello World");

    std::cout << std::endl << std::endl << "Link: ";
    auto textBlock4{ new Link(new Text()) };
    textBlock4->render("netology.ru","Hello World");
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

