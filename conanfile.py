from conans import ConanFile, MSBuild, tools


class Dasm6502Conan(ConanFile):
    name = "6502dasm"
    version = "1.0.0"
    license = ""
    author = "Tom Aviv TomAviv57@gmail.com"
    url = "https://github.com/ETLCPP/etl.git"
    description = "C++ library to disassemble 6502 assembly"
    topics = ("6502", "disassembler", "library")
    settings = "os"  # , "compiler", "build_type", "arch"

    RESOURCES_FOLDER_NAME = "Resources"

    def requirements(self):
        self.requires("etl/20.24.1")

    def validate(self):
        pass

    def imports(self):
        self.copy("*.h", dst=Dasm6502Conan.RESOURCES_FOLDER_NAME)

    def package_info(self):
        self.cpp_info.includedirs = [rf"..\${Dasm6502Conan.RESOURCES_FOLDER_NAME}\include"]
        self.cpp_info.defines = ["USE_ETL"] if self.settings.use_etl else []

    def build(self):
        if self.settings.os == "Windows":
            msbuild = MSBuild(self)
            msbuild.build_env.include_paths(rf"..\${Dasm6502Conan.RESOURCES_FOLDER_NAME}\include")
            msbuild.build(r"VisualStudio\6502dasm.sln")
