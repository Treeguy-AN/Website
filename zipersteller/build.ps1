$sfml = "C:\Users\tbaum\OneDrive\Desktop\SFML-2.6.2"

$gameFolder = "..\Game"
$output = "release"
$zipName = "realm-fighters.zip"
$downloadFolder = "..\downloads"

if (Test-Path $output) {
    Remove-Item $output -Recurse -Force
}

New-Item -ItemType Directory -Path $output | Out-Null

g++ `
"$gameFolder\main.cpp" `
"$gameFolder\game.cpp" `
"$gameFolder\fighter.cpp" `
-o "$output\realm-fighters.exe" `
-I"$sfml\include" `
-L"$sfml\lib" `
-lsfml-graphics `
-lsfml-window `
-lsfml-system

Copy-Item "$sfml\bin\sfml-graphics-2.dll" $output
Copy-Item "$sfml\bin\sfml-window-2.dll" $output
Copy-Item "$sfml\bin\sfml-system-2.dll" $output

Copy-Item "$gameFolder\arial.ttf" $output -ErrorAction SilentlyContinue

if (!(Test-Path $downloadFolder)) {
    New-Item -ItemType Directory -Path $downloadFolder | Out-Null
}

Compress-Archive -Path "$output\*" -DestinationPath "$downloadFolder\$zipName" -Force

Write-Host "ZIP erstellt:"
Write-Host "$downloadFolder\$zipName"