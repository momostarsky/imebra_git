#import "objc_imebra.mm"

int main() {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    LoadDicom *loadDicom = [[LoadDicom alloc] init];
    [loadDicom loadFile:@"/home/paolo/Documents/dicom standard/image_0"];

    // Display the patient name
    ///////////////////////////
    printf("%s", [[loadDicom getTagString:16 forGroup:16] UTF8String]);

    [loadDicom release];
}
