
struct tf32 {

  unsigned int data;

  public:
    tf32() {
      data = 0;
    }

    tf32(float t_floatVal) {
      data = (*reinterpret_cast<unsigned int *>(&t_floatVal)) >> 13;
    }

    tf32(double t_doubleVal) {
      float floatVal = (float)t_doubleVal;
      data = (*reinterpret_cast<unsigned int *>(&floatVal)) >> 13;
    }

    //cast to float
    operator float(){
      unsigned int extendedData = data << 13;
      return *reinterpret_cast<float*>(&extendedData);
    }

    //cast to tf32
    tf32& operator =(float t_floatVal) {
      data = (*reinterpret_cast<unsigned int *>(&t_floatVal)) >> 13;
      return *this;
    }
};

