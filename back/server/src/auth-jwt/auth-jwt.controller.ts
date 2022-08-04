import { Controller, Get, Post, Body, Patch, Param, Delete, UseGuards, Res } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { AuthJwtService } from './auth-jwt.service';
import { Response } from 'express';

@Controller('auth-jwt')
export class AuthJwtController {
  constructor(
    private readonly authJwtService: AuthJwtService) {}

  @Get("access/:intra_id")
  createaccessJwt(@Param("intra_id") intra_id:string) {
    return this.authJwtService.createAccessJwt(intra_id);
  }

  @Get("access/:intra_id")
  createRefreshJwt(@Param("intra_id") intra_id:string) {
    return this.authJwtService.createRefreshJwt(intra_id);
  }

  @Get("refresh")
  @UseGuards(AuthGuard('jwt-refresh-token'))
  refresh() {
    return ("refresh 성공");
  }

  @Get("access")
  @UseGuards(AuthGuard('jwt-access-token'))
  access() {
    return "access 성공";
  }

  @Get("test")
  cookieTest(@Res() res: Response)
  {
    console.log("확인")

    res.cookie('v1',"v1",{
      httpOnly: true,
      maxAge: 24 * 60 * 60 * 1000
    });
		res.cookie('v2',"v2",{
			httpOnly: true,
			maxAge: 24 * 60 * 60 * 1000
		});


    return(res.redirect("http://localhost:3000"));
  }
}
