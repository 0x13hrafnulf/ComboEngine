#include <string>


class Attributes
{
    private:

    //SDL attributes
    int m_width; 
    int m_height;
    std::string m_title;

    //


    public:

    //SDL setters & getters
    void SetWindowWidth(int new_width)
    {
        m_width = new_width;
    }   
    void SetWindowHeight(int new_height)
    {
        m_height = new_height;
    }

    int GetWindowWidth() const
    {
        return m_width;
    }   
    int GetWindowHeight() const
    {
        return m_height;
    }
    const std::string& GetWindowTitle() const
    {
        return m_title;
    }

    //

};