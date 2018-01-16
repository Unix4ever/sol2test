import os

from conans import ConanFile, CMake, tools

class GsageConan(ConanFile):
    name = "sol2test"
    version = "1.0"
    license = "MIT"
    url = "-"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "with_lua_version": ["luajit-2.0.5"]
    }
    default_options = (
        "shared=False",
        "with_lua_version=luajit-2.0.5",
    )
    generators = "cmake"

    def config_options(self):
        lua, version = str(self.options.with_lua_version).split("-")

        self.requires.add("{}-rocks/{}@gsage/master".format(lua, version), private=True)
        self.requires.add("OGRE/1.9.0@gsage/master", private=True)
        self.options["OGRE"].with_boost = self.settings.os != "Windows"
        self.options["OGRE"].shared = self.settings.os == "Windows"

    def build(self):
        cmake = CMake(self)
        options = {
            "CMAKE_INSTALL_PREFIX": "./sdk",
            "CMAKE_BUILD_TYPE": self.settings.build_type,
        }

        cmake.configure(defs=options, build_dir='build')
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="build/bin", src="bin")
        self.copy("*.dylib", dst="build/bin", src="lib")
        self.copy("libluajit.*", dst="resources/luarocks/lib", src="lib")
        self.copy("luajit", dst="resources/luarocks/bin", src="bin")
        self.copy("*.*", dst="resources/luarocks/etc", src="etc")
        self.copy("*.lua", dst="resources/luarocks", src="share")
        self.copy("*.*", dst="resources/luarocks/tools", src="tools")
        self.copy("lua*.h*", dst="resources/luarocks/include", src="include")
        self.copy("lauxlib.h*", dst="resources/luarocks/include", src="include")

    def package(self):
        pass

    def package_info(self):
        self.cpp_info.libs = []
