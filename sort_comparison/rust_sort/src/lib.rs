// expose sort function to sort a buffer of size 3 to C code

// Note: &mut [i32] is not FFI safe
// &mut [i32] is a reference to a slice of i32 values and thus int32_t (*buf)[3]

#[no_mangle]
pub extern "C" fn sort3_rust_std(buf: *mut i32) {
    // Safety: We assume that `buf` points to an array of 3 `int32_t` values.
    // We also assume that it's a valid pointer passed from C.
    unsafe {
        let buf_slice = std::slice::from_raw_parts_mut(buf, 3);
        buf_slice.sort();
    }
}

#[no_mangle]
pub extern "C" fn sort3_rust_swap_inline_annotated(buf_raw: *mut i32) {
    unsafe {
        let buf = std::slice::from_raw_parts_mut(buf_raw, 3);
        if buf[0] > buf[1] {
            buf.swap(0, 1);
        }
        if buf[1] > buf[2] {
            buf.swap(1, 2);
        }
        if buf[0] > buf[1] {
            buf.swap(0, 1);
        }
    }
}

#[no_mangle]
pub extern "C" fn sort3_rust_swap_inline_raw(buf: *mut i32) {
    unsafe {
        if *buf.offset(0) > *buf.offset(1) {
            let tmp = *buf.offset(0);
            *buf.offset(0) = *buf.offset(1);
            *buf.offset(1) = tmp;
        }
        if *buf.offset(1) > *buf.offset(2) {
            let tmp = *buf.offset(1);
            *buf.offset(1) = *buf.offset(2);
            *buf.offset(2) = tmp;
        }
        if *buf.offset(0) > *buf.offset(1) {
            let tmp = *buf.offset(0);
            *buf.offset(0) = *buf.offset(1);
            *buf.offset(1) = tmp;
        }
    }
}

#[no_mangle]
pub extern "C" fn sort3_rust_branchless_min_annotated(buf_raw: *mut i32) {
    unsafe {
        let buf = std::slice::from_raw_parts_mut(buf_raw, 3);

        let a = buf[0];
        let b = buf[1];
        let c = buf[2];

        let min_val = a.min(b).min(c);
        let max_val = a.max(b).max(c);
        let middle_val = a + b + c - min_val - max_val;

        buf[0] = min_val;
        buf[1] = middle_val;
        buf[2] = max_val;

        // let a = buf[0];
        // let b = buf[1];
        // let c = buf[2];
        // let ab = a.min(b);
        // let ac = a.min(c);
        // let bc = b.min(c);
        // let abc = ab.min(c);
        // buf[0] = abc;
        // buf[1] = if abc == a { bc } else { ac };
        // buf[2] = if abc == c { ab } else { bc };
    }
}


#[no_mangle]
pub extern "C" fn sort3_rust_branchless_annotated(buf_raw: *mut i32) {
    unsafe {
        let buf = std::slice::from_raw_parts_mut(buf_raw, 3);
        let a = buf[0];
        let b = buf[1];
        let c = buf[2];
        let x = (a > b) as usize;
        let y = (a > c) as usize;
        let z = (b > c) as usize;
        buf[x+y] = a;
        buf[1-x+z] = b;
        buf[2-y-z] = c;
    }
}
