$sfml = "C:\Users\tbaum\OneDrive\Desktop\SFML-2.6.2"

$root = ".."

$gameFolder = "$root\Game"
$launcherFolder = "$root\Launcher"

$gameRelease = "$gameFolder\release"
$launcherRelease = "$launcherFolder\release"

$downloadFolder = "$root\downloads"

if (Test-Path $gameRelease) {
    Remove-Item $gameRelease -Recurse -Force
}

if (Test-Path $launcherRelease) {
    Remove-Item $launcherRelease -Recurse -Force
}

New-Item -ItemType Directory -Path $gameRelease | Out-Null
New-Item -ItemType Directory -Path $launcherRelease | Out-Null

if (!(Test-Path $downloadFolder)) {
    New-Item -ItemType Directory -Path $downloadFolder | Out-Null
}

g++ `
"$gameFolder\main.cpp" `
"$gameFolder\game.cpp" `
"$gameFolder\fighter.cpp" `
-o "$gameRelease\realm-fighters.exe" `
-I"$sfml\include" `
-L"$sfml\lib" `
-lsfml-graphics `
-lsfml-window `
-lsfml-system

Copy-Item "$sfml\bin\sfml-graphics-2.dll" $gameRelease
Copy-Item "$sfml\bin\sfml-window-2.dll" $gameRelease
Copy-Item "$sfml\bin\sfml-system-2.dll" $gameRelease

New-Item -ItemType Directory -Path "$gameRelease\assets\fonts" -Force | Out-Null
Copy-Item "$gameFolder\assets\fonts\arial.ttf" "$gameRelease\assets\fonts\arial.ttf" -Force

Compress-Archive `
-Path "$gameRelease\*" `
-DestinationPath "$downloadFolder\realm-fighters.zip" `
-Force

g++ `
"$launcherFolder\launcher.cpp" `
-o "$launcherRelease\launcher.exe" `
-I"$sfml\include" `
-L"$sfml\lib" `
-lsfml-graphics `
-lsfml-window `
-lsfml-system

Copy-Item "$sfml\bin\sfml-graphics-2.dll" $launcherRelease
Copy-Item "$sfml\bin\sfml-window-2.dll" $launcherRelease
Copy-Item "$sfml\bin\sfml-system-2.dll" $launcherRelease

Compress-Archive `
-Path "$launcherRelease\*" `
-DestinationPath "$downloadFolder\launcher.zip" `
-Force

Write-Host ""
Write-Host "Build erfolgreich!"
Write-Host "Spiel ZIP: $downloadFolder\realm-fighters.zip"
Write-Host "Launcher ZIP: $downloadFolder\launcher.zip"