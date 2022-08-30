import { CanActivate, ExecutionContext, Injectable } from "@nestjs/common";
import { Request } from "express";
import { Observable } from "rxjs";
import { AuthService } from "./auth.service";

@Injectable()
export class AuthGuard implements CanActivate {
	constructor(private authService: AuthService) { }

	canActivate(
		context: ExecutionContext,
	): boolean | Promise<boolean> | Observable<boolean> {
		const request = context.switchToHttp().getRequest();
		return this.validateRequest(request);
	}

	private validateRequest(request: Request) {
		const tokenString = request.headers.authorization.split('Bearer ')[1];
		// console.log(tokenString);
		// if (AuthService.tokens.has(tokenString))
		// {
		// 	return true;
		// }
		// else
			return false;
	}
}
