rule rootkit_LD_PRELOAD
{ 
    strings:
        $func = "readdir" ascii //readdir is being obstructed
        $sym1 = "dlsym" ascii 
        $target = "secret.txt" ascii //hidden file

    condition:
        $func and $sym1 and $target //must all be in place in the file

}
