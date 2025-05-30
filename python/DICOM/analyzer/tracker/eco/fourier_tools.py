import numpy as np

np.seterr(divide='ignore', invalid='ignore')

def fft2(x):
    return np.fft.fft(np.fft.fft(x, axis=1), axis=0).astype(np.complex64)
    # return fft(fft(x, axis=1), axis=0)

def ifft2(x):
    return np.fft.ifft(np.fft.ifft(x, axis=1), axis=0).astype(np.complex64)
    # return ifft(ifft(x, axis=1), axis=0)

def cfft2(x):
    in_shape = x.shape
    # if both dimensions are odd
    if in_shape[0] % 2 == 1 and in_shape[1] % 2 == 1:
        xf = np.fft.fftshift(np.fft.fftshift(fft2(x), 0), 1).astype(np.complex64)
    else:
        out_shape = list(in_shape)
        out_shape[0] =  in_shape[0] + (in_shape[0] + 1) % 2
        out_shape[1] =  in_shape[1] + (in_shape[1] + 1) % 2
        out_shape = tuple(out_shape)
        xf = np.zeros(out_shape, dtype=np.complex64)
        xf[:in_shape[0], :in_shape[1]] = np.fft.fftshift(np.fft.fftshift(fft2(x), 0), 1).astype(np.complex64)
        if out_shape[0] != in_shape[0]:
            xf[-1,:] = np.conj(xf[0,::-1])
        if out_shape[1] != in_shape[1]:
            xf[:,-1] = np.conj(xf[::-1,0])
    return xf

def cifft2(xf):
    x = np.real(ifft2(np.fft.ifftshift(np.fft.ifftshift(xf, 0),1))).astype(np.float32)
    return x

def compact_fourier_coeff(xf):
    """
        creates a compact fourier series representation by removing the strict
        right half pane
    """
    if isinstance(xf, list):
        return [x[:, :(x.shape[1]+1)//2, :] for x in xf]
    else:
        return xf[:, :(xf.shape[1]+1)//2, :]

def cubic_spline_fourier(f, a):
    """
        The continuous fourier transform of a cubic spline kernel
    """
    bf = - ( - 12 * a + 12 * np.exp( - np.pi * f * 2j) + 12 * np.exp(np.pi * f * 2j) + 6 * a * np.exp(-np.pi * f * 4j) + \
        6 * a * np.exp(np.pi * f * 4j) + f * (np.pi * np.exp(-np.pi*f*2j)*12j) - f * (np.pi * np.exp(np.pi * f * 2j) * 12j) + \
        a*f*(np.pi*np.exp(-np.pi*f*2j)*16j) - a * f * (np.pi*np.exp(np.pi*f*2j)*16j) + \
        a*f*(np.pi*np.exp(-np.pi*f*4j)*4j) - a * f * (np.pi*np.exp(np.pi*f*4j)*4j)-24)
    bf /= (16 * f ** 4 * np.pi ** 4)
    # bf[f != 0] /= (16 * f**4 * np.pi**4)[f != 0]
    bf[f == 0] = 1
    return bf

def full_fourier_coeff(xf):
    """
        Reconstructs the full Fourier series coefficients
    """
    xf = [np.concatenate([xf_, np.conj(np.rot90(xf_[:, :-1,:], 2))], axis=1) for xf_ in xf]
    return xf

def interpolate_dft(xf, interp1_fs, interp2_fs):
    """
        performs the implicit interpolation in the fourier domain of a sample
        by multiplying with the fourier coefficients of the interpolation function
    """
    return [xf_ * interp1_fs_ * interp2_fs_
            for xf_, interp1_fs_, interp2_fs_ in zip(xf, interp1_fs, interp2_fs)]


def resize_dft(inputdft, desired_len):
    """
        resize a one-dimensional DFT to the desired length.
    """
    input_len = len(inputdft)
    minsz = min(input_len, desired_len)

    scaling = desired_len / input_len

    resize_dft = np.zeros(desired_len, dtype=inputdft.dtype)

    mids = int(np.ceil(minsz / 2))
    mide = int(np.floor((minsz - 1) / 2))

    resize_dft[:mids] = scaling * inputdft[:mids]
    resize_dft[-mide:] = scaling * inputdft[-mide:]
    return resize_dft

def sample_fs(xf, grid_sz=None):
    sz = xf.shape[:2]
    if grid_sz is None or sz == grid_sz:
        x = sz[0] * sz[1] * cifft2(xf)
    else:
        sz = np.array(sz)
        grid_sz = np.array(grid_sz)
        if np.any(grid_sz < sz):
            raise("The grid size must be larger than or equal to the siganl size")
        tot_pad = grid_sz - sz
        pad_sz = np.ceil(tot_pad / 2).astype(np.int32)
        xf_pad = np.pad(xf, tuple(pad_sz), 'constant')
        if np.any(tot_pad % 2 == 1):
            xf_pad = xf_pad[:xf_pad.shape[0]-(tot_pad[0] % 2), :xf_pad.shape[1]-(tot_pad[1] % 2)]
        x = grid_sz[0] * grid_sz[1] * cifft2(xf_pad)
    return x

def shift_sample(xf, shift, kx, ky):
    shift_exp_y = [np.exp(1j * shift[0] * ky_).astype(np.complex64) for ky_ in ky]
    shift_exp_x = [np.exp(1j * shift[1] * kx_).astype(np.complex64) for kx_ in kx]
    xf = [xf_ * sy_.reshape(-1, 1, 1, 1) * sx_.reshape((1, -1, 1, 1))
            for xf_, sy_, sx_ in zip(xf, shift_exp_y, shift_exp_x)]
    return xf

def symmetrize_filter(hf):
    """
        ensure hermetian symmetry
    """
    for i in range(len(hf)):
        dc_ind = int((hf[i].shape[0]+1) / 2)
        hf[i][dc_ind:, -1, :] = np.conj(np.flipud(hf[i][:dc_ind-1, -1, :]))
    return hf
