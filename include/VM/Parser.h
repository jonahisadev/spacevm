#ifndef SPACE_PARSER_H
#define SPACE_PARSER_H

namespace VM {
    
    class Parser {
    private:
        char* text;
        
    public:
        Parser(char* text);
        ~Parser();
        
        void start();
    }
    
} // namespace VM

#endif // SPACE_PARSER_H