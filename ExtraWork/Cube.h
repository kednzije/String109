class Cube {
    private: 
        double m_x;
        static int numOfObject;
    public:
        Cube();
        ~Cube();
        void set(double x);
        double getVolume();
        static void displayNumOfObject();
};