// swift-tools-version:4.0

import PackageDescription

let package = Package(
    name: "libtess",
    products: [
        .library(name: "libtess",type: .static,targets: ["libtess"])
    ],
    targets: [
        .target(name: "libtess",dependencies: [],path:"Sources/libtess")
    ]
)
