function expose_module_to_global(module) {
    Object.keys(module).forEach(key => eval("let " + key + "=" + module[key]));
}
