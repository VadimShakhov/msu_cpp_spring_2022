struct Data2uint{
    uint64_t a;
    uint64_t b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

struct Data3uint{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data2bool{
    bool a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

struct Data3bool{
    bool a;
    bool b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data_ibib{
    uint64_t a;
    bool b;
    uint64_t c;
    bool d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }
};

struct Data_double{
    uint64_t a;
    bool b;
    double c;
    bool d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }
};
