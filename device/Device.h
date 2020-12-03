
class Device{
private:
    const char* name;
    // 10 commands, max 15 chars long
    const char commands[16] = {
        '0','0','0','0',
        '1','0','0','1',
        '0','1','1','0',
        '1','0','1','1'
        };
        
    char operationResult[1024];
public:
    Device(const char* name);
    const char* getName();
    void setOperationResult(char*);
    const char* getOperationResult();
    const char* getWord(const char , const char ,char*);
};

