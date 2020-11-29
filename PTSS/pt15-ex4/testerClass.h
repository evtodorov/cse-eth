#ifndef TESTERCLASS_H
#define TESTERCLASS_H


class testerClass
{
    public:
        /** Default constructor */
        testerClass();
        /** Default destructor */
        virtual ~testerClass();
        /** Copy constructor
         *  \param other Object to copy from
         */
        testerClass(const testerClass& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        testerClass& operator=(const testerClass& other);
        /** Access m_Counter
         * \return The current value of m_Counter
         */
        unsigned int GetCounter() { return m_Counter; }
        /** Set m_Counter
         * \param val New value to set
         */
        void SetCounter(unsigned int val) { m_Counter = val; }
    protected:
    private:
        unsigned int m_Counter; //!< Member variable "m_Counter"
};

#endif // TESTERCLASS_H
