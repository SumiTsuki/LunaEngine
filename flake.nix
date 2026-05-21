{
  description = "Vulkan development environment.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
      in
        {
          devShells.default = pkgs.mkShell {
            nativeBuildInputs = with pkgs; [
              gcc
              gdb
              clang-tools
              gnumake
              ninja
              cmake
              pkg-config
            ];
            buildInputs = with pkgs; [
              sdl3
              vulkan-headers
            ];
            shellHook = ''
                      echo "Vulkan Development Environment."
            '';
          };
        }
    );
}
