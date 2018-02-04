CONFIGURATION	=	Release
PLATFORM	=	ubuntu.16.10-x64

all:
	dotnet build -r $(PLATFORM)
	dotnet publish -c $(CONFIGURATION) -r $(PLATFORM)

init:	clean
	dotnet restore

clean:
	rm -fr obj bin
	rm -f *~
