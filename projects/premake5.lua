include("../../garrysmod_common")
--include(path.join("../../garrysmod_common", "generator.v2.lua"))

platforms{ "linux", "windows" }

CreateWorkspace({name = "hookproxy"})
	CreateProject({serverside = true})

		includedirs({"../includes", "../source"})

		IncludeLuaShared()
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()

		files {
			"../source/**.cpp",
			"../source/**.hpp",
			"../source/**.h",
			"../includes/**.h",
			"../includes/**.cpp",
		}

		filter { "platforms:windows" }
			defines {
				"_WIN32",
				"GMMODULE",
				"GMOD_ALLOW_DEPRECATED",
			}

		filter { "platforms:linux" }
			defines {
				"__linux__",
				"GMMODULE",
				"GMOD_ALLOW_DEPRECATED",
			}
