{
  description = "Flake to build the C++ project";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };
    in
    {
      devShells.${system}.default =
        pkgs.mkShell.override
          {
            stdenv = pkgs.clangStdenv;
          }
          {
            packages = with pkgs; [
              cmake
              tbb # multiple thread support for std::execution
              gnuplot # dependancies for matplotpp
              pkg-config
              libpng
              libjpeg
              libwebp
              libtiff
              zstd
              libdeflate
              jbigkit
              xz
              cacert # purify the flake
              git
            ];
          };
    };
}
