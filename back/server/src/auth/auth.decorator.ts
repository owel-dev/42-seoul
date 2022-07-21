import { createParamDecorator, ExecutionContext } from "@nestjs/common";

export const Token = createParamDecorator(
	(data: unknown, ctx: ExecutionContext) => {
		const header = ctx.switchToHttp().getRequest().headers;
		return (header.authorization.split('Bearer ')[1]);
	}
)