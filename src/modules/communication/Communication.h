enum class ErrorStatus {
    Success,
    ErrorSetup,
    ErrorConnect,
    ErrorSend,
    ErrorRecieve,
    ErrorProcess,
    ErrorClose
    //...
};

class	Communication {
    public:
        virtual ErrorStatus setup() = 0;
        virtual ErrorStatus connect() = 0;
        virtual ErrorStatus send() = 0;
        virtual ErrorStatus recieve() = 0;
        virtual ErrorStatus process() = 0;
        virtual ErrorStatus close() = 0;
};
