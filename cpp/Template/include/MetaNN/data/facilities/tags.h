#ifndef METANN_DATA_FACILITIES_TAGS_H
#define METANN_DATA_FACILITIES_TAGS_H

/**
 * @brief: This file defines some category tags and device tags.
 * Use these tags to classify the data type and device type.
 */

namespace MetaNN {

// category tags
struct CategoryTags {
    struct Scalar {};
    struct Matrix {};
    struct BatchScalar {};
    struct BatchMatrix {};
};

/// device types
struct DeviceTags {
    struct CPU;
};

} // namespace MetaNN

#endif // METANN_DATA_FACILITIES_TAGS_H