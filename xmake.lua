add_rules("mode.debug", "mode.release")

add_requires("minifb", "miniaudio")

target("minipntr")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("minifb", "miniaudio")
    add_includedirs("src/external")
    if is_plat("wasm") then
        set_extension(".mjs")
        add_ldflags("-sASYNCIFY -sSINGLE_FILE -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=FS")
    end
