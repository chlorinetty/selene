Import("env")
from pathlib import Path
import subprocess

#* output path
out = Path(env.subst("$PROJECT_DIR")) / "lib" / "selene" / "seleneinfo.hxx"

#* helpers
def git():
    return subprocess.check_output("git rev-parse --short HEAD", shell=True).decode().strip()

#* info
hash = git()

#* outputting
out.parent.mkdir(parents=True, exist_ok=True)

out.write_text(f"""\
inline constexpr const char* SELENEVERSION = "0.1.0";
inline constexpr const char* SELENEVERSIONHASH = "{hash}";

inline constexpr const char* SELENEAUTHOR = "Akseli Rinne<akseli@awrinne.fi>";
inline constexpr const char* SELENELICENSE = "Apache-2.0";
""")