{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    forAllSystems = fn:
      nixpkgs.lib.genAttrs nixpkgs.lib.platforms.linux (
        system: fn nixpkgs.legacyPackages.${system}
      );
  in {
    devShells = forAllSystems (pkgs: rec {
      default = pkgs.mkShellNoCC {
        packages = with pkgs; [
          gcc
          clang-tools
        ];
      };
    });

    formatter = forAllSystems (pkgs: pkgs.alejandra);
  };
}
