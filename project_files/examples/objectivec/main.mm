#import "objc_dataset.mm"

int main() {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    ImebraDataSet *loadDicom = [[ImebraDataSet alloc] init];
    [loadDicom loadFile:@"/home/paolo/Documents/dicom standard/image_0"];

    // Display the patient name
    ///////////////////////////
    printf("%s", [[loadDicom getStringFromGroup:16 inTag:16] UTF8String]);

    [loadDicom release];
}
