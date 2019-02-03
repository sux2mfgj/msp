#include <FlightController.hpp>
#include <iostream>

struct MyIdent : public msp::Message {
    MyIdent(msp::FirmwareVariant v) : Message(v) {}

    msp::ID id() const { return msp::ID::MSP_IDENT; }

    msp::ByteVector raw_data;

    virtual bool decode(const msp::ByteVector &data) override {
        raw_data = data;
        return true;
    }
};

struct Callbacks {
    void onIdent(const MyIdent &ident) {
        std::cout << "Raw Ident data: ";
        for(auto d : ident.raw_data) {
            std::cout << int(d) << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    const int port = 1612;

    Callbacks cbs;
    fcu::FlightController fcu;
    fcu.connect(port);

    // subscribe with costum type
    fcu.subscribe(&Callbacks::onIdent, &cbs, 1);

    // Ctrl+C to quit
    std::cin.get();
}
