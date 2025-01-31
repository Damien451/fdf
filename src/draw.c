/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:02:05 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/02 17:07:38 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "math.h"
#include "libft.h"

static int	put_strings_crea(t_fdf *fdf)
{
	mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
		fdf->canvas.w_width - 215, 1,
		0x79ff4d, "IJKL to select pixel");
	mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
		fdf->canvas.w_width - 215, 18,
		0x79ff4d, "TG to change altitude");
	mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
		fdf->canvas.w_width - 215, 35,
		0x79ff4d, "Numpad (8462) to move");
	mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
		fdf->canvas.w_width - 215, 52,
		0x79ff4d, "vertice");
	return (0);
}

static int	put_strings(t_fdf *fdf)
{
	char	gauge[26];

	ft_memset(gauge, '.', 25);
	gauge[25] = 0;
	gauge[0] = '-';
	gauge[24] = '+';
	gauge[1] = '[';
	gauge[23] = ']';
	gauge[((int)(fdf->relief * 10)) + 12] = '|';
	if (fdf->hud)
	{
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 1, 0x79ff4d, "WASD to move camera");
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 18, 0x79ff4d, "QE to zoom/dezoom");
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 35, 0x79ff4d, "ArrowKeys to rotate");
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 52, 0x79ff4d, gauge);
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 69, 0x79ff4d, "C to enable crea mode");
		mlx_string_put(fdf->canvas.mlx_ptr, fdf->canvas.window,
			1, 86, 0x79ff4d, "TAB to hide HUD");
	}
	return (fdf->crea.mode && fdf->hud ? put_strings_crea(fdf) : 0);
}

int			draw_map(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	ft_bzero(fdf->canvas.img.img, (int)fdf->canvas.w_width
			* (int)fdf->canvas.w_height * sizeof(int));
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->project[y * fdf->width + x] = project_point(fdf, x, y);
			++x;
		}
		++y;
	}
	put_pixels(fdf);
	if (fdf->crea.mode)
		put_circle(fdf);
	mlx_put_image_to_window(fdf->canvas.mlx_ptr, fdf->canvas.window,
		fdf->canvas.img.img_ptr, 0, 0);
	put_strings(fdf);
	return (0);
}
