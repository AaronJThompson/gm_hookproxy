include("../../garrysmod_common")
--include(path.join("../../garrysmod_common", "generator.v2.lua"))

platforms{ "linux", "windows" }

CreateWorkspace({name = "hookproxy"})
	CreateProject({serverside = true, source_path = "source/menu", manual_files = true})

		includedirs({"../includes", "../source/menu"})

		IncludeLuaShared()
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()

		files {
			"../source/menu/**.cpp",
			"../source/menu/**.hpp",
			"../source/menu/**.h",
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

	CreateProject({serverside = false, source_path = "source/client", manual_files = true})

		includedirs({"../includes", "../source/client"})

		IncludeLuaShared()
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()

		files {
			"../source/client/**.cpp",
			"../source/client/**.hpp",
			"../source/client/**.h",
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

