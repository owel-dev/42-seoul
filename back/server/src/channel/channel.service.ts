import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { getConnection, getRepository, QueryBuilder, Repository } from 'typeorm';
import { PostChannelDto } from './dto/post-channel.dto';
import { UpdateChannelDto } from './dto/update-channel.dto';
import { ChannelEntity } from './entities/channel.entity';

@Injectable()
export class ChannelService {
  constructor (
    @Inject('CHANNEL_REPOSITORY')
    private channelRepository: Repository<ChannelEntity>
  ){}

  async createChannel(postChannelDto: PostChannelDto) {
    const channel = new ChannelEntity();
    channel.player1 = postChannelDto.player1;
    channel.player2 = postChannelDto.player2;
    channel.admin = postChannelDto.admin;
    channel.curNumUser = 0;
    channel.maxNumUser = 10;
    channel.password = postChannelDto.password;
    channel.mode = postChannelDto.mode;
    channel.type = postChannelDto.type;

    await this.channelRepository.save(channel);
  }

  async getAllChannelList() {
    const result = await this.channelRepository.find();
    return result;
  }

  async getOneChannel(channelid: number) {
    const result = await this.channelRepository.findOneBy({channelId : channelid});
    return result;
  }

  async updatePassword(channelid: number, updateChannelDto: UpdateChannelDto) {
    await this.channelRepository.update(channelid, {password: updateChannelDto.password});

  }

  async updateCurNumUser(channelid: number) {
    const chnnelUpdate = await this.channelRepository.findOneBy({channelId : channelid});
    chnnelUpdate.curNumUser += 1;
    await this.channelRepository.update(channelid, {curNumUser: chnnelUpdate.curNumUser});
  }

  remove(channelid: number) {
    return `This action removes a #${channelid} channel`;
  }
}
