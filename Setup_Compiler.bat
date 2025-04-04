@echo off
setlocal enabledelayedexpansion

:: Set the project root directory
set PROJECT_DIR=%CD%
set BUILD_DIR=%PROJECT_DIR%\build
set REPO_URL=https://github.com/youruser/yourrepository.git

:: Logo File and Icon Setup
set ICON_FILE=%PROJECT_DIR%\resources\eighleaux_logo.ico

:: Check for required dependencies (git, cmake, g++, make, libcurl)
echo Checking dependencies...

:: Check for Git
where git >nul 2>nul
if errorlevel 1 (
    echo Git is not installed. Installing Git...
    call :installGit
)

:: Check for CMake
where cmake >nul 2>nul
if errorlevel 1 (
    echo CMake is not installed. Installing CMake...
    call :installCMake
)

:: Check for g++
where g++ >nul 2>nul
if errorlevel 1 (
    echo g++ is not installed. Installing g++...
    call :installGpp
)

:: Check for make
where make >nul 2>nul
if errorlevel 1 (
    echo make is not installed. Installing make...
    call :installMake
)

:: Check for libcurl
where curl >nul 2>nul
if errorlevel 1 (
    echo libcurl is not installed. Installing libcurl...
    call :installLibCurl
)

:: Check for required icon/logo file
if not exist "%ICON_FILE%" (
    echo Eighleaux logo not found. Downloading logo...
    call :downloadLogo
)

:: Clone the repository if it does not exist
if not exist "%PROJECT_DIR%\yourrepository" (
    echo Cloning repository...
    git clone %REPO_URL% %PROJECT_DIR%\yourrepository
)

:: Go to the project directory
cd %PROJECT_DIR%\yourrepository

:: Run CMake to configure the project
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo Running CMake to configure the build...
cmake ..

:: Build the project using make
echo Building the project...
make

:: Add custom icon/logo to the executable (assuming Windows .exe output)
echo Adding Eighleaux logo to the executable...
call :addIconToExe "%PROJECT_DIR%\yourrepository\build\advanced_compiler.exe" "%ICON_FILE%"

echo Build and setup complete. Run the program using the 'advanced_compiler' executable in the build directory.

:: End script
endlocal
exit /b

:: Functions for installation of dependencies
:installGit
echo Installing Git...
:: You can change this for your system's preferred package manager or download method
choco install git
goto :eof

:installCMake
echo Installing CMake...
:: Install CMake via Chocolatey (Windows package manager)
choco install cmake
goto :eof

:installGpp
echo Installing g++...
:: Install g++ via Chocolatey (Windows package manager)
choco install mingw
goto :eof

:installMake
echo Installing make...
:: Install make via Chocolatey
choco install make
goto :eof

:installLibCurl
echo Installing libcurl...
:: Download libcurl from official site or use a package manager like choco
choco install curl
goto :eof

:downloadLogo
echo Downloading Eighleaux logo...
:: Download the logo using curl
curl -o "%ICON_FILE%" https://example.com/eighleaux_logo.ico
goto :eof

:addIconToExe
:: This function adds the custom icon/logo to the executable using a resource editor or command-line tool.
:: In this case, we can use a tool like ResourceHacker (https://www.angusj.com/resourcehacker/) to change the icon of the .exe file.
:: Make sure you have ResourceHacker installed and available in your PATH, or download it manually.

echo Adding icon to executable...
:: Assuming ResourceHacker is installed or present in the project directory
ResourceHacker.exe -open %1 -save %1 -action addoverwrite -res "%ICON_FILE%" -mask ICONGROUP,1,
goto :eof
