$sfml = "C:\Users\tbaum\OneDrive\Desktop\SFML-2.6.2"

$root = ".."

$gameFolder = "$root\Game"
$releaseFolder = "$gameFolder\release"

$downloadFolder = "$root\downloads"

$zipName = "realm-fighters.zip"

if (Test-Path $releaseFolder) {
    Remove-Item $releaseFolder -Recurse -Force
}

New-Item -ItemType Directory -Path $releaseFolder | Out-Null

g++ `
"$gameFolder\main.cpp" `
"$gameFolder\game.cpp" `
"$gameFolder\fighter.cpp" `
-o "$releaseFolder\realm-fighters.exe" `
-I"$sfml\include" `
-L"$sfml\lib" `
-lsfml-graphics `
-lsfml-window `
-lsfml-system

Copy-Item "$sfml\bin\sfml-graphics-2.dll" $releaseFolder
Copy-Item "$sfml\bin\sfml-window-2.dll" $releaseFolder
Copy-Item "$sfml\bin\sfml-system-2.dll" $releaseFolder

New-Item -ItemType Directory -Path "$releaseFolder\assets\fonts" -Force | Out-Null

Copy-Item `
"$gameFolder\assets\fonts\arial.ttf" `
"$releaseFolder\assets\fonts\arial.ttf" `
-Force

if (!(Test-Path $downloadFolder)) {
    New-Item -ItemType Directory -Path $downloadFolder | Out-Null
}

Compress-Archive `
-Path "$releaseFolder\*" `
-DestinationPath "$downloadFolder\$zipName" `
-Force

Write-Host ""
Write-Host "Build erfolgreich!"
Write-Host ""
Write-Host "Release Ordner:"
Write-Host $releaseFolder
Write-Host ""
Write-Host "ZIP:"
Write-Host "$downloadFolder\$zipName"