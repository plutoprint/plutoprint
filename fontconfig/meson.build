fontconfig_files = run_command(
    python, '-c', 'import glob; print("\\n".join(glob.glob("**/*.conf", recursive=True)))',
    check: true
).stdout().strip()

if fontconfig_files != ''
    install_data(fontconfig_files.split('\n'), install_dir: python.get_install_dir() / 'plutoprint' / 'fontconfig', preserve_path: true)
endif
