#import "objc_helpers.h"

int main() {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    // Try a cyrillic /greek/latin patient name
    std::wstring patientName0 = L"\x0430\x0402\x0403\x00c9^\x00d0\x0410\x00d5";
    std::wstring patientName1 = L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072";

    NSString* str = StringWToNSString(patientName0);
    std::wstring convertedPatientName0(NSStringToStringW(str));
}
