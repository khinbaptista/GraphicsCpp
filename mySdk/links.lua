local thisDirectory = os.getcwd();

local LinkFuncs =
{
	sdl = function()
		includedirs "SDL2/include"
		libdirs "SDL2/lib/x86"

		configuration "Debug"
			links {"SDL2", "SDL2main", "opengl32"}

		configuration "Release"
			links {"SDL2", "SDL2main", "opengl32"}
	end,
	glew = function()
		includedirs "glew/include"
		libdirs "glew/lib/Release/Win32"

		configuration "Debug"
			links {"glew32"}

		configuration "Release"
			links {"glew32"}
	end,
	glm = function()
		includedirs "glm"
	end,
}

local function ProcTable(tbl)
	for i, lib in ipairs(tbl) do
		if(type(lib) == "string") then
			if(not LinkFuncs[lib]) then
				print("Bad library named ", lib);
			else
				local prevDir = os.getcwd()
				os.chdir(thisDirectory)
				configuration {}

				LinkFuncs[lib]()
				
				configuration {}
				os.chdir(prevDir)
			end
		elseif(type(lib) == "table") then
			ProcTable(lib);
		end
	end
end

function UseLibs(...)
	local libList = {...}
	ProcTable(libList)
end
