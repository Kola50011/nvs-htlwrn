
class Calc
{
  private:
    int akk;

  public:
    Calc(){
        akk = 0;
    };

    int add(int value)
    {
        akk += value;
        return akk;
    };

    int mul(int value)
    {
        for (int i{2}; i <= value; i++)
        {
            add(akk);
        }
        return akk;
    };

    int value()
    {
        return akk;
    }
};